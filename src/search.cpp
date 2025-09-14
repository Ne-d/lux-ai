#include "search.h"

#include "lux/game_objects.hpp"
#include "lux/map.hpp"

using namespace lux;

Cell* findClosestResourceTile(const Unit& unit, Player& player, std::vector<Cell*> resourceTiles)
{
	Cell *closestResourceTile = nullptr;
	float closestDist = 9999999;
	for (auto it = resourceTiles.begin(); it != resourceTiles.end(); it++)
	{
		auto* cell = *it;
		if (cell->resource.type == ResourceType::coal && !player.researchedCoal()) continue;
		if (cell->resource.type == ResourceType::uranium && !player.researchedUranium()) continue;
		float const dist = cell->pos.distanceTo(unit.pos);
		if (dist < closestDist)
		{
			closestDist = dist;
			closestResourceTile = cell;
		}
	}

	return closestResourceTile;
}


lux::CityTile* findClosestCityTile(const lux::Unit& unit, lux::Player& player)
{
	auto city_iter = player.cities.begin();
	auto &city = city_iter->second;

	float closestDist = 999999;
	CityTile *closestCityTile = nullptr;
	for (auto &citytile : city.citytiles)
	{
		float dist = citytile.pos.distanceTo(unit.pos);
		if (dist < closestDist)
		{
			closestCityTile = &citytile;
			closestDist = dist;
		}
	}

	return closestCityTile;
}


const Cell* findTileToBuild(const lux::City& city, const GameMap& gameMap)
{
	constexpr DIRECTIONS directions[] = {EAST, SOUTH, WEST, NORTH};

	// Search in every tile of the given city
	for (const CityTile& cityTile : city.citytiles)
	{
		// Look at every adjacent tile
		for (const DIRECTIONS direction : directions)
		{
			const Cell* cell = gameMap.getCellByPos(cityTile.pos.translate(direction, 1));
			if (isCellEmpty(cell))
				return cell;
		}
	}

	return nullptr;
}


bool isCellEmpty(const lux::Cell* cell)
{
	return cell->citytile == nullptr && !cell->hasResource();
}


lux::DIRECTIONS rotateDirection(const lux::DIRECTIONS direction, const unsigned int rotation)
{
	if (direction == CENTER)
		return CENTER;

	constexpr DIRECTIONS directions[] = {EAST, SOUTH, WEST, NORTH};
	int currentIndex = 0;

	switch (direction)
	{
	case EAST:
		currentIndex = 0; break;
	case SOUTH:
		currentIndex = 1; break;
	case WEST:
		currentIndex = 2; break;
	case NORTH:
		currentIndex = 3; break;
	}

	return directions[(currentIndex + rotation) % 4];
}
