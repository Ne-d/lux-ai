#include "search.h"

#include "lux/game_objects.hpp"
#include "lux/map.hpp"

// Adapted from the Lux C++ kit.
lux::Cell* findClosestResourceTile(const lux::Unit& unit, lux::Player& player, std::vector<lux::Cell*> resourceTiles)
{
	lux::Cell*closestResourceTile = nullptr;
	float closestDist = 9999999;

	for (auto it = resourceTiles.begin(); it != resourceTiles.end(); it++)
	{
		auto* cell = *it;
		if (cell->resource.type == lux::ResourceType::coal && !player.researchedCoal()) continue;
		if (cell->resource.type == lux::ResourceType::uranium && !player.researchedUranium()) continue;
		float const dist = cell->pos.distanceTo(unit.pos);
		if (dist < closestDist)
		{
			closestDist = dist;
			closestResourceTile = cell;
		}
	}

	return closestResourceTile;
}

// Adapted from the Lux c++ kit
lux::CityTile* findClosestCityTile(const lux::Unit& unit, lux::Player& player)
{
	auto city_iter = player.cities.begin();
	auto &city = city_iter->second;

	float closestDist = 999999;
	lux::CityTile*closestCityTile = nullptr;

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


const lux::Cell* findTileToBuild(const lux::City& city, const lux::GameMap& gameMap)
{
	constexpr lux::DIRECTIONS directions[] = { lux::EAST, lux::SOUTH, lux::WEST, lux::NORTH };

	// Search in every tile of the given city
	for (const lux::CityTile& cityTile : city.citytiles)
	{
		// Look at every adjacent tile
		const int start = rand() % 4;
		for (int i = start; i < start + 4; i++)
		{
			const lux::Cell* cell = gameMap.getCellByPos(cityTile.pos.translate(directions[i % 4], 1));
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
	if (direction == lux::CENTER)
		return lux::CENTER;

	// Forgive me for my sins.
	constexpr lux::DIRECTIONS directions[] = { lux::EAST, lux::SOUTH, lux::WEST, lux::NORTH };
	int currentIndex = 0;

	switch (direction)
	{
	case lux::EAST:
		currentIndex = 0; break;
	case lux::SOUTH:
		currentIndex = 1; break;
	case lux::WEST:
		currentIndex = 2; break;
	case lux::NORTH:
		currentIndex = 3; break;
	}

	return directions[(currentIndex + rotation) % 4];
}
