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

/**
 * Returns the closest resource tile to the given unit.
 */
lux::Cell* findClosestResourceTile(const lux::Unit& unit, lux::Player& player, std::vector<lux::Cell*> resourceTiles);

/**
 * Returns the closest city tile to the given unit.
 */
lux::CityTile* findClosestCityTile(const lux::Unit& unit, lux::Player& player);

/**
 * Find a cell adjacent to the given city that is empty and can be built on.
 */
const lux::Cell* findTileToBuild(const lux::City& city, const lux::GameMap& gameMap);

/**
 * Returns true if the cell is empty (has no CityTile or Resource), false if the cell is not empty.
 */
bool isCellEmpty(const lux::Cell* cell);

/**
 * Computes the rotated version of a given direction.
 * @param direction The direction to rotate.
 * @param rotation The amount of rotation to apply (in 90 degree increments, clockwise)
 * @return The direction rotated by the given amount.
 */
lux::DIRECTIONS rotateDirection(lux::DIRECTIONS direction, unsigned int rotation);