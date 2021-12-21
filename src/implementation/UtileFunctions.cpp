#include "UtileFunctions.h"


void drawColoredSpace(int x, int y, int color, char character) {
	attron(COLOR_PAIR(color));
	mvaddch(y, x, character);
	attroff(COLOR_PAIR(color));
}

bool pressedDirection(int dir) {
	return (dir == KEY_DOWN || dir == KEY_LEFT || dir == KEY_RIGHT || dir == KEY_UP);
}

void clearStr(int xMin, int xMax, int y){
	for(int i = xMin; i <= xMax; i++)
		mvaddch(y, i, ' ');
}

WorldCoordinate random_range(Boundary& range) {
	std::srand(time(NULL));
	int x = std::rand() % (range.coordRightDown.x - range.coordLeftUp.x) + range.coordLeftUp.x;
	int y = std::rand() % (range.coordRightDown.y - range.coordLeftUp.y) + range.coordLeftUp.y;
	return WorldCoordinate{x, y};
}

/*	Проверка на столкновне героя с объектом. 
	Если координаты героя входят во множество координат
	одной граничной стороны, то возвращается true, иначе false.
	Key необходим для определения граничной стороны, которая будет
	сравниваться с героем*/
bool intersects(Object* b1, Object* b2) {
	if( dynamic_cast<SingleCellObject*>(b2) ) {
		if( ( (*b1).coordinate.y == (*b2).coordinate.y) &&
			( (*b1).coordinate.x == (*b2).coordinate.x ) )
		{
			//collision()
			return true;
		}
	}else if( dynamic_cast<MultipleCellObject*>(b2) ) {
		if( ( (*b1).coordinate.y == (*b2).boundary.coordLeftUp.y ) && 
			( (*b2).boundary.coordRightDown.x >= (*b1).coordinate.x &&
			(*b2).boundary.coordLeftUp.x <= (*b1).coordinate.x) )
		{
			//collision()
			return true;
		}
		else if( ( (*b1).coordinate.y == (*b2).boundary.coordRightDown.y) && 
				  ( (*b2).boundary.coordRightDown.x >= (*b1).coordinate.x &&
				  (*b2).boundary.coordLeftUp.x <= (*b1).coordinate.x) )
		{
			//collision()
			return true;
		}
		else if( ( (*b1).coordinate.x == (*b2).boundary.coordRightDown.x) &&
				  ( (*b2).boundary.coordRightDown.y >= (*b1).coordinate.y &&
				  (*b2).boundary.coordLeftUp.y <= (*b1).coordinate.y) )
		{
			//collision()
			return true;
		}
		else if( ( (*b1).coordinate.x == (*b2).boundary.coordLeftUp.x) &&
				  ( (*b2).boundary.coordRightDown.y >= (*b1).coordinate.y &&
				  (*b2).boundary.coordLeftUp.y <= (*b1).coordinate.y) )
		{
			//collision()
			return true;
		}
	}
	return false;	
}

bool intersects(const WCoord& wCoord, Object* b2) {
	if( dynamic_cast<SingleCellObject*>(b2) ) {
		if( ( wCoord.y == (*b2).coordinate.y) &&
			( wCoord.x == (*b2).coordinate.x ) )
		{
			//collision()
			return true;
		}
	}else if( dynamic_cast<MultipleCellObject*>(b2) ) {
		if( ( wCoord.y == (*b2).boundary.coordLeftUp.y ) && 
			( (*b2).boundary.coordRightDown.x >= wCoord.x &&
			(*b2).boundary.coordLeftUp.x <= wCoord.x) )
		{
			//collision()
			return true;
		}
		else if( ( wCoord.y == (*b2).boundary.coordRightDown.y) && 
				  ( (*b2).boundary.coordRightDown.x >= wCoord.x &&
				  (*b2).boundary.coordLeftUp.x <= wCoord.x) )
		{
			//collision()
			return true;
		}
		else if( ( wCoord.x == (*b2).boundary.coordRightDown.x) &&
				  ( (*b2).boundary.coordRightDown.y >= wCoord.y &&
				  (*b2).boundary.coordLeftUp.y <= wCoord.y) )
		{
			//collision()
			return true;
		}
		else if( ( wCoord.x == (*b2).boundary.coordLeftUp.x) &&
				  ( (*b2).boundary.coordRightDown.y >= wCoord.y &&
				  (*b2).boundary.coordLeftUp.y <= wCoord.y) )
		{
			//collision()
			return true;
		}
	}
	return false;	
}