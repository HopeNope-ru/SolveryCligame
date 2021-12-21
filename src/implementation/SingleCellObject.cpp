#include "SingleCellObject.h"

SingleCellObject::SingleCellObject(int x_, int y_, double damage, int color_,
	char character_, uint64_t cooldown, GameState* gameState_) 
	: Object(x_, y_, color_, character_, gameState_)
{
	this->damage = damage;
	turnTime = cooldown;
	gameState->gridIndex->GetObjectInPoint(coordinate).push_back(this);
	iterGrid = --gameState->gridIndex->GetObjectInPoint(coordinate).end();
}

SingleCellObject::SingleCellObject(WCoord wCoord, 
	uint64_t cooldown, GameState* game)
	: Object(wCoord, game), turnTime(cooldown)
{ }

void SingleCellObject::draw() {
	gameState->camera->drawColoredSpaceInCamCoords(coordinate, color, character);
	// drawColoredSpace(coordinate.x, coordinate.y, color, character);
}

void SingleCellObject::move(const WorldCoordinate& delta) {
	// Изменяем игровое время, следующим ходом объекта.
	gameState->gameTime = nextTurn;
	// Обновляем следующий ход, указывающий на время через которое
	// объект будет ходить.
	nextTurn = gameState->gameTime + turnTime;
	
	bool flagIntersects = false;
	
	WorldCoordinate coordTemp;
	coordTemp = this->coordinate;
	this->coordinate.x += delta.x;
	this->coordinate.y += delta.y;
	
	/*
		В цикле производится проверка на пересечения с объектом.
	Если проверяемый объект пересекся с любым другим, то
	завершается работа и координаты объекта вовращаются к
	исходному значению
	*/
	for( auto collider : gameState->gridIndex->GetObjectInPoint(coordinate) ) {
		if( collider != this ) 
			if( intersects(this, collider) ){
				this->onCollision(collider);
				collider->onCollision(this);
				flagIntersects = true;
				break;
			}
	}

	for( auto colliderWall : *(gameState->MCObjects) ) {
		if( intersects(this, colliderWall) ){
			this->onCollision(colliderWall);
			colliderWall->onCollision(this);
			flagIntersects = true;
			break;
		}
	}

	if(flagIntersects) {
		this->coordinate = coordTemp;
	}else{
		/*	
			1)	Если не было пересечения с объектом, то так же проверить на видимость в камере
				объекта.
			2)	Производится проверка на нахождения объекта в пространственном индексе, и если
				объект перешел в другую часть пространства, то удалится из прошлого просранства
				и добавится в текущее место
		*/
		if( gameState->gridIndex->GetObjectInPoint(coordinate) != 
			gameState->gridIndex->GetObjectInPoint(coordTemp) ) 
		{
			gameState->gridIndex->GetObjectInPoint(coordTemp).remove(*iterGrid);
			gameState->gridIndex->GetObjectInPoint(coordinate).push_back(this);
			iterGrid = --gameState->gridIndex->GetObjectInPoint(coordinate).end();
		}
	}
}