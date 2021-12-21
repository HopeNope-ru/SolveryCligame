#include "UI.h"

UI::UI(Hero *hero_) : hero(hero_) {
	coordinate.x = getmaxx(stdscr) - 15;
	coordinate.y = 5;
}

void UI::draw() {
	mvprintw(coordinate.y, coordinate.x, "health: %.1f", hero->health); 
}

void UI::update() {
	draw();
}