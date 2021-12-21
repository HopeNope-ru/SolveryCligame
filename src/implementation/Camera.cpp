#include "Camera.h"

Camera::Camera(Object* heroFollowing_, Object* frontier_) 
	: heroFollowing(heroFollowing_), frontier(frontier_)
{
	coordinate.x = heroFollowing->coordinate.x;
	coordinate.y = heroFollowing->coordinate.y;

	WCoord offset{10, 10};
	boundary.coordLeftUp = coordinate - offset;
	boundary.coordRightDown = coordinate + offset;
	
	// Проверка выхода границы камеры за границы камеры
	if(frontier->boundary.coordLeftUp.x > boundary.coordLeftUp.x) {
		// Ищем смещение от границы карты до границы камеры
		WCoord offset{
			std::abs(frontier->boundary.coordLeftUp.x - boundary.coordLeftUp.x),
			0
		};
		// Смещаем камеру вправо
		boundary.coordLeftUp = boundary.coordLeftUp + offset;
		boundary.coordRightDown = boundary.coordRightDown + offset;
		coordinate = coordinate + offset;
	}

	if(frontier->boundary.coordLeftUp.y > boundary.coordLeftUp.y) {
		WCoord offset{
			0,
			std::abs(frontier->boundary.coordLeftUp.y - boundary.coordLeftUp.y)
		};
		// Смещаем камеру вниз
		boundary.coordLeftUp = boundary.coordLeftUp + offset;
		boundary.coordRightDown = boundary.coordRightDown + offset;
		coordinate = coordinate + offset;
	}

	if(frontier->boundary.coordRightDown.x < boundary.coordRightDown.x) {
		WCoord offset{
			std::abs(frontier->boundary.coordRightDown.x - boundary.coordRightDown.x),
			0
		};
		// Смещаем камеру влево
		boundary.coordRightDown = boundary.coordRightDown - offset;
		boundary.coordLeftUp = boundary.coordLeftUp - offset;
		coordinate = coordinate - offset;
	}

	if(frontier->boundary.coordRightDown.y < boundary.coordRightDown.y) {
		WCoord offset{
			0,
			std::abs(frontier->boundary.coordRightDown.y - boundary.coordRightDown.y)
		};
		// Смещаем камеру вверх
		boundary.coordRightDown = boundary.coordRightDown - offset;
		boundary.coordLeftUp = boundary.coordLeftUp - offset;
		coordinate = coordinate - offset;
	}
}

void Camera::drawColoredSpaceInCamCoords(const WCoord& coord, int color, char character) {
	WCoord world2cam = coord - boundary.coordLeftUp;
	attron(COLOR_PAIR(color));
	mvaddch(world2cam.y, world2cam.x, character);
	attroff(COLOR_PAIR(color));
}

void Camera::move(const WorldCoordinate& delta) {
	// Hero передает delta
	// Прошлая граница камеры нужна для подчистки хвостов от объектов
	lastBoundCam = boundary;
	// Создаем задержку для камеры, т.к она может запаздывать за героем или опережать его
	// Так же нужно будет при проверке условий
	WCoord delayCamera = coordinate + delta;
	Boundary delayBoundary { 
		boundary.coordLeftUp + delta, 
		boundary.coordRightDown + delta
	};

	// Камера не подвижна в четырех углах, а так же зафиксирована на одной из оси
	// находясь на границе мира. Для движения камеры, ей необходимо выполнить следующие условия:
	// 1) Граница камеры должна находиться в пределах мира
	// 2) Герой должен попасть на одну из осей центра камеры
	if( delayBoundary.coordLeftUp.x >= frontier->boundary.coordLeftUp.x &&
		delayBoundary.coordRightDown.x <= frontier->boundary.coordRightDown.x &&
		heroFollowing->coordinate.x == delayCamera.x)
	{
		coordinate.x += delta.x;
		boundary.coordLeftUp.x += delta.x;
		boundary.coordRightDown.x += delta.x;	
	}

	if( delayBoundary.coordLeftUp.y >= frontier->boundary.coordLeftUp.y &&
		delayBoundary.coordRightDown.y <= frontier->boundary.coordRightDown.y &&
		heroFollowing->coordinate.y == delayCamera.y)
	{
		coordinate.y += delta.y;
		boundary.coordLeftUp.y += delta.y;
		boundary.coordRightDown.y += delta.y;	
	}
}