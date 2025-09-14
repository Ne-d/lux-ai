#pragma once

#include <vector>

#include "lux/city.hpp"

namespace lux
{
	class GameMap;
	class Unit;
	class Player;
	class Cell;
}

lux::Cell* findClosestResourceTile(const lux::Unit& unit, lux::Player& player, std::vector<lux::Cell*> resourceTiles);
lux::CityTile* findClosestCityTile(const lux::Unit& unit, lux::Player& player);
const lux::Cell* findTileToBuild(const lux::City& city, const lux::GameMap& gameMap);
bool isCellEmpty(const lux::Cell* cell);
lux::DIRECTIONS rotateDirection(lux::DIRECTIONS direction, unsigned int rotation);