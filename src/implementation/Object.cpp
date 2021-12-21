#include "Object.h"

Object::Object(int x_, int y_, int color_, char character_, GameState* gameState_){
	coordinate.x = x_;
	coordinate.y = y_;
	color = color_;
	character = character_;
	gameState = gameState_;
}

Object::Object(WCoord wCoord, GameState* game) {
	coordinate = wCoord;
	gameState = game;
}
