#include "Coordinate.h"

WorldCoordinate WorldCoordinate::operator+ (const WorldCoordinate& coord) const{
    return WorldCoordinate{ x + coord.x, y + coord.y };
}

WorldCoordinate WorldCoordinate::operator- (const WorldCoordinate& coord) const{
    return WorldCoordinate{ x - coord.x, y - coord.y };
}

bool operator== (const WorldCoordinate& coord1, const WorldCoordinate& coord2) {
    return (coord1.x == coord2.x && coord1.y == coord2.y);
}

bool operator!= (const WorldCoordinate& coord1, const WorldCoordinate& coord2) {
    return !(coord1 == coord2);
}

bool operator< (const WorldCoordinate& coord1, const WorldCoordinate& coord2) {
    if(coord1.x < coord2.x)
        return true;
    else if(coord1.y < coord2.y && coord1.x == coord2.x)
        return true;
    else 
        return false;
}

bool operator== (const LocalCoordinate& coord1, const LocalCoordinate& coord2) {
    return (coord1.x == coord2.x && coord1.y == coord2.y);
}

bool operator!= (const LocalCoordinate& coord1, const LocalCoordinate& coord2) {
    return !(coord1 == coord2);
}

bool operator< (const LocalCoordinate& coord1, const LocalCoordinate& coord2) {
    if(coord1.x < coord2.x)
        return true;
    else if(coord1.y < coord2.y && coord1.x == coord2.x)
        return true;
    else 
        return false;
}