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
