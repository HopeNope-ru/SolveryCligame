#include "Monsters.h"

Monsters::Monsters(int x_, int y_, double damage, int color_, double health_, char character_, uint64_t cdMove, GameState* gameState_) 
	: SingleCellObject(x_, y_, damage, color_, character_, cdMove, gameState_),
	  DamageReceived(health_)
{
	// Добавляем монстров в менеджер объектов и в очередь 
	gameState->managerObjects->push_back(this);
	iterMngObj = --gameState->managerObjects->end();
	gameState->turnQueue.push(this);
}

bool Monsters::destroy() {
	if(death)
		mvaddch(coordinate.y, coordinate.x, ' ');
	return death;
}

void Monsters::onCollision(Object* other) {
	if( Hero* h = dynamic_cast<Hero*>(other) )
		takeDamage(h->damage);
}

void Monsters::takeDamage(double damage) {
	health -= damage;
}

void Monsters::update() {
	// Движение монстров за героем

	Node start{coordinate};
	Node goal{gameState->hero->coordinate};

	std::map<WCoord, Node> all_nodes;

	all_nodes = astar(start, goal, gameState);

	std::list<WCoord> path = path_fun(start, goal, all_nodes);
	std::list<WCoord>::iterator itPath = path.begin();
	// прибавляем что бы взять координату не равную start
	itPath++;

	WCoord& coord_move = *itPath;

	WCoord delta;
	delta.x = coord_move.x - coordinate.x;
	delta.y = coord_move.y - coordinate.y;

	move(WCoord{delta.x, delta.y});

	if(health <= 0){
		death = true;
		// Убираем из всех контейнеров объект
		gameState->managerObjects->remove(*iterMngObj);
		gameState->gridIndex->GetObjectInPoint(coordinate).remove(*iterGrid);
		return;
	}
}