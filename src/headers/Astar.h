#pragma once
#include "Defs.h"
#include "Hero.h"
#include "Monsters.h"
#include "Coordinate.h"
#include "UtileFunctions.h"

struct Node {
    WCoord coordinate;
    WCoord came_from;
    float cost = 0.0f;
    float priority;

    bool operator== (const Node& node);
};

std::map<WCoord, Node> astar(const Node& start, const Node& goal, GameState* gameState);
std::list<WCoord> path_fun(const Node& start, const  Node& goal, std::map<WCoord, Node>& all_nodes);