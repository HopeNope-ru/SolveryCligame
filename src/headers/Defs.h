#pragma once
#include <ncurses.h>
#include <memory>
#include <list>
#include <vector>
#include <stdlib.h>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <functional>
#include <iostream>

class Object;
class SingleCellObject;
class Item;
class MultipleCellObject;
class Hero;
class Camera;
class GridIndex;
struct WorldCoordinate;
struct LocalCoordinate;

using ListSCObject = std::list<SingleCellObject*>;
using ListMCObject = std::list<MultipleCellObject*>;
using ListItem = std::list<Item*>;
using WCoord = WorldCoordinate;
using LCoord = LocalCoordinate;
using ObjectTurnQueue = std::priority_queue<SingleCellObject*, std::vector<SingleCellObject*>, std::function<bool(SingleCellObject*, SingleCellObject*)>>;

enum e_color_pair {E_WALL = 1, E_HERO, E_MONSTR, E_EMPTY, E_POWERUP};

const int WINDOW_X = 120;
const int WINDOW_Y = 40;
const int SIZE_CELL_XxY = 4;


struct GameState {
	ObjectTurnQueue turnQueue;
	ListSCObject* managerObjects;
	ListMCObject* MCObjects;
	ListItem* managerItems;
	GridIndex* gridIndex;
	Camera* camera;
	Hero* hero;
	uint64_t gameTime = 0ULL;
	bool exit = false;
};
