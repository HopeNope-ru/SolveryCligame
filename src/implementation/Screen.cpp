#include "Screen.h"

Screen::Screen(Boundary sizeScreenBoundary) : sizeBound(sizeScreenBoundary)
{
	viewBound.coordLeftUp = sizeBound.coordLeftUp;
	viewBound.coordRightDown.y = sizeBound.coordRightDown.y;

	int offset = 20;
	viewBound.coordRightDown.x = sizeBound.coordRightDown.x - offset; 
}

bool Screen::outFrontierScreen(LocalCoordinate& prevCamera) {
	if( viewBound.coordLeftUp.x >= prevCamera.x ||
		viewBound.coordLeftUp.y >= prevCamera.y ||
		viewBound.coordRightDown.y <= prevCamera.y ||
		viewBound.coordRightDown.x <= prevCamera.x )
	{
		return true;
	}
	return false;
}
