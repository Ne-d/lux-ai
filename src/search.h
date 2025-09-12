#pragma once

#include <vector>

#include "lux/city.hpp"

namespace lux
{
	class Unit;
	class Player;
	class Cell;
}

lux::Cell* findClosestResourceTile(const lux::Unit& unit, lux::Player& player, std::vector<lux::Cell*> resourceTiles);
lux::CityTile* findClosestCityTile(const lux::Unit& unit, lux::Player& player);