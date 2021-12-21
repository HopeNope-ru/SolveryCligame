#pragma once

struct WorldCoordinate {
	int x;
	int y;

    WorldCoordinate operator+ (const WorldCoordinate& coord) const;
    WorldCoordinate operator- (const WorldCoordinate& coord) const;

    friend bool operator== (const WorldCoordinate& coord1, const WorldCoordinate& coord2);
    friend bool operator!= (const WorldCoordinate& coord1, const WorldCoordinate& coord2);
    friend bool operator< (const WorldCoordinate& coord1, const WorldCoordinate& coord2);
};

struct LocalCoordinate {
	int x;
	int y;

    friend bool operator== (const LocalCoordinate& coord1, const LocalCoordinate& coord2);
    friend bool operator!= (const LocalCoordinate& coord1, const LocalCoordinate& coord2);
    friend bool operator< (const LocalCoordinate& coord1, const LocalCoordinate& coord2);
};