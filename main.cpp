#include "Defs.h"
#include "Boundary.h"
#include "UtileFunctions.h"
#include "GridIndex.h"
#include "Object.h"
#include "Camera.h"
#include "MultipleCellObject.h"
#include "Column.h"
#include "Wall.h"
#include "Spawner.h"
#include "DamageReceived.h"
#include "SingleCellObject.h"
#include "Hero.h"
#include "Monsters.h"
#include "UI.h"
#include "SingleCellObjectStatic.h"
#include "SpeedUp.h"
#include "DoubleDamage.h"
#include "Status.h"
#include "PowerupItem.h"
#include "ApliedStatus.h"
#include "LinuxMagic.h"

int main()
{	
	magic_init();
	std::cerr << "log" << std::endl;
	initscr();			/* Start curses mode 		  */
	raw();
	noecho();	
	curs_set(0);
	keypad(stdscr, true);
	start_color();
	init_pair(E_WALL, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(E_HERO, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(E_MONSTR, COLOR_RED, COLOR_RED);
	init_pair(E_EMPTY, COLOR_BLACK, COLOR_BLACK);
	init_pair(E_POWERUP, COLOR_CYAN, COLOR_BLACK);
	
	GameState gameState;
	GridIndex gridIndex;
	ListSCObject managerObjects;
	ListMCObject MCObjects;
	ListItem managerItems;
	std::map<Status::Kind, ApliedStatus> status;

	// Добавление powerup'ов
	SpeedUp speedUp(10, 2);
	PowerupItem speedItem(Status::SPEEDUP, WCoord{10,10}, E_POWERUP, 'S', &gameState, &speedUp);
	managerItems.push_back(&speedItem);

	DoubleDamage dd(10, 2.0);
	PowerupItem ddItem(Status::DD, WCoord{20, 20}, E_POWERUP, 'D', &gameState, &dd);
	managerItems.push_back(&ddItem);

	Boundary sizeScreenBoundary{ 0, 0, WINDOW_X, WINDOW_Y};

	// приоритетная очередь для поочередного движения объектов
	auto cmp = [](SingleCellObject* SCObj1, SingleCellObject*SCObj2) {
		return SCObj1->nextTurn > SCObj2->nextTurn;
	};

	gameState.turnQueue = ObjectTurnQueue(cmp);
	gameState.gridIndex = &gridIndex;
	gameState.managerObjects = &managerObjects;
	gameState.MCObjects = &MCObjects;
	gameState.managerItems = &managerItems;

	ApliedStatus apSpeedUp(&speedUp, &gameState);
	ApliedStatus apDD(&dd, &gameState);

	status.emplace(Status::SPEEDUP,  apSpeedUp);
	status.emplace(Status::DD, apDD);

	Hero* hero = new Hero(5, 9, 5.5, E_HERO, 100.0, ' ', 2, &gameState, status);
	Wall* wallInit = new Wall(Boundary{0,0,WINDOW_X - 20, WINDOW_Y - 1}, E_WALL, ' ', &gameState);
	Column* column = new Column(5, 5,Boundary{10,6,15,8}, E_WALL, ' ', &gameState);
	
	Monsters* monster[4];

	UI uiHero(hero);
	Camera camera(hero, wallInit);

	gameState.camera = &camera;
	gameState.hero = hero;

	Spawner spawner(WorldCoordinate{60, 10}, 20, &gameState);

	for(int i = 0; i < 4; i++){
		monster[i] = new Monsters(20+2*i, 7+2*i, 20.5, E_MONSTR, 50.0, ' ', 3, &gameState);
		monster[i]->draw();
	}
	hero->draw();
	uiHero.draw();
	wallInit->draw();
	column->draw();
	speedItem.draw();
	
	while (!gameState.exit) {
		for(auto item: managerItems) {
			item->draw();
		}

		SingleCellObject* nextChar = gameState.turnQueue.top();
		gameState.turnQueue.pop();
		nextChar->update();

		if( !(nextChar->destroy()) ) {
			gameState.turnQueue.push(nextChar);
		}else{
			// Отдаем системе память
			delete nextChar;
		}

		if(hero->destroy()){
			clear();
			mvprintw( getmaxy(stdscr) / 2, getmaxx(stdscr) / 2, "YOU DIED");
			break;
		}

		// очищаем экран и рисуем новые положения
		clear();
		for(auto obj: MCObjects) {
			obj->update();
		}

		for(auto obj: managerObjects)
			obj->draw();
	
		uiHero.update();
	}

	// отдаем зарезервированную память системе
	auto delndestroy = [](auto del) {
		if(!(del->destroy())) {
			delete del;
			return true;
		}else
			return false;
	};
	managerObjects.remove_if(delndestroy);

	MCObjects.remove(wallInit);
	MCObjects.remove(column);
	delete wallInit;
	delete column;

	endwin();			/* End curses mode		  */
	return 0;
}
