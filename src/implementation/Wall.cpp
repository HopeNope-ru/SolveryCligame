#include "Wall.h"


Wall::Wall(Boundary bound, int color_, char character_, GameState* gameState_)
	: MultipleCellObject(0, 0, bound, color_, character_, gameState_)
{ }

void Wall::draw() {
	// Рисуем стены
	// Верхняя часть
	for (int i = 0; i < boundary.coordRightDown.x; ++i)
		gameState->camera->drawColoredSpaceInCamCoords(WCoord{i, 0}, color, character);
	// Левая часть
	for (int i = 0; i < boundary.coordRightDown.y + 1; ++i)
		gameState->camera->drawColoredSpaceInCamCoords(WCoord{0, i}, color, character);
	// Нижняя часть
	for (int i = 0; i < boundary.coordRightDown.x + 1; ++i)
		gameState->camera->drawColoredSpaceInCamCoords(WCoord{i, boundary.coordRightDown.y}, color, character);
	// Правая часть
	for (int i = 0; i < boundary.coordRightDown.y; ++i)
		gameState->camera->drawColoredSpaceInCamCoords(WCoord{boundary.coordRightDown.x, i}, color, character);
}

void Wall::update() {
	draw();
}