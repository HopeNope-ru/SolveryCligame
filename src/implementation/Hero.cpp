#include "Hero.h"

Hero::Hero(int x_, int y_, double damage, int color_, double health_,
	char character_, uint64_t cdMove, GameState* gameState_, std::map<Status::Kind, ApliedStatus>& status_) 
	: SingleCellObject(x_, y_, damage, color_, character_, cdMove, gameState_),
	  DamageReceived(health_), status(status_)
{
	// Добавляем героя в менеджер объектов и в очередь
	gameState->managerObjects->push_back(this);
	iterMngObj = gameState->managerObjects->end();
	gameState->turnQueue.push(this);
}

void Hero::UsePowerup(Status::Kind nameStatus) {
	if( item.count(nameStatus) && !(item.at(nameStatus).empty()) && (!status.count(nameStatus) || !(status.at(nameStatus).IsAplied()) ) ) {
		status.at(nameStatus).Apply(this);
		item.at(nameStatus).pop();
	}
}

void Hero::PickUp() {
	for( auto& item: *(gameState->managerItems) ) {
		if( coordinate == item->coordinate )
			item->OnPickup();
	}
}

void Hero::PushItem(Status::Kind nameItem, Item* item) {
	this->item[nameItem].push(item);
}

void Hero::move(const WorldCoordinate& delta) {
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
			}
	}

	for( auto colliderWall : *(gameState->MCObjects) ) {
		if( intersects(this, colliderWall) ){
			this->onCollision(colliderWall);
			colliderWall->onCollision(this);
			flagIntersects = true;
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
				и добавится в текущий индекс
		*/
		gameState->camera->move(delta);
		if( gameState->gridIndex->GetObjectInPoint(coordinate) != 
			gameState->gridIndex->GetObjectInPoint(coordTemp) ) 
		{
			gameState->gridIndex->GetObjectInPoint(coordTemp).remove(*iterGrid);
			gameState->gridIndex->GetObjectInPoint(coordinate).push_back(this);
			iterGrid = --gameState->gridIndex->GetObjectInPoint(coordinate).end();
		}
	}
}

bool Hero::destroy() {
	return death;
}

void Hero::onCollision(Object* other) {
	if( SingleCellObject* sco = dynamic_cast<SingleCellObject*>(other) ) {
		takeDamage(sco->damage);
	}
}

void Hero::takeDamage(double damage){
	health -= damage;
}

void Hero::update() {
	std::cerr << "speed: " << turnTime << std::endl;
	std::cerr << "damage: " << damage << std::endl;
	refresh();
	int c;
	bool pressed_direction = true;
	do {
		c = getch();
		pressed_direction = true;
		switch (c) {
			case KEY_UP:
				move(WCoord{0, -1});
				break;
			case KEY_LEFT:
				move(WCoord{-1, 0});
				break;
			case KEY_RIGHT:
				move(WCoord{1, 0});
				break;
			case KEY_DOWN:
				move(WCoord{0, 1});
				break;
			case KEY_BACKSPACE:
				gameState->exit = true;
				break;
			case 'f':
				PickUp();
				pressed_direction = false;
				break;
			case '1':
				std::cerr << "size item speedup: " << item[Status::SPEEDUP].size() << std::endl; 
				UsePowerup(Status::SPEEDUP);
				pressed_direction = false;
				break;
			case '2':
				UsePowerup(Status::DD);
				pressed_direction = false;
				break;
		}
	}while( !pressed_direction && !gameState->exit );

	if(health <= 0) {
		health = 0;
		death = true;
		// Убираем объект из всех контейнеров
		gameState->managerObjects->remove(*iterMngObj);
		gameState->gridIndex->GetObjectInPoint(coordinate).remove(*iterGrid);
		return;
	}else if(health < 100)
		health += 2.5;
	
	if(health > 100) {
		health = 100;
	}
}