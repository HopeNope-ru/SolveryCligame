#include "Boundary.h"

void Boundary::mirrorCoordinate(WCoord& coordLeftDown, WCoord& coordRightUp) const{
	//смещение координат относительно оси границы
	coordLeftDown.x = coordLeftUp.x; 
	coordLeftDown.y = coordRightDown.y;
	coordRightUp.x = coordRightDown.x;
	coordRightUp.y = coordLeftUp.y;
}