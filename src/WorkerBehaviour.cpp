#include "WorkerBehaviour.h"

#include "AgentManager.h"
#include "Objective.h"
#include "search.h"

namespace lux
{
	class Cell;
}


void WorkerBehaviour::collectFuel(const lux::Unit& unit, lux::Player player, const std::vector<lux::Cell*>& resourceTiles)
{
	const lux::Cell *closestResourceTile = findClosestResourceTile(unit, player, resourceTiles);

	if (closestResourceTile != nullptr)
	{
		const auto dir = unit.pos.directionTo(closestResourceTile->pos);
		AgentManager::addAction(unit.move(dir));
	}
}


void WorkerBehaviour::deposit(const lux::Unit& unit, lux::Player player)
{
	// Go to the nearest city
	const lux::CityTile *closestCityTile = findClosestCityTile(unit, player);
	if (closestCityTile != nullptr)
	{
		const auto dir = unit.pos.directionTo(closestCityTile->pos);
		AgentManager::addAction(unit.move(dir));
	}
}


void WorkerBehaviour::collectWood()
{
}


void WorkerBehaviour::buildCity(const lux::Unit& unit, lux::Player player, const lux::GameMap& gameMap)
{
	const lux::CityTile *closestCityTile = findClosestCityTile(unit, player);
	if (closestCityTile->pos.distanceTo(unit.pos) <= 1 && unit.canBuild(gameMap) && unit.canAct())
	{
		AgentManager::addAction(unit.move(lux::DIRECTIONS::WEST)); // TODO: Find available tile
		AgentManager::addAction(unit.buildCity());
	}
	else
	{
		deposit(unit, player);
	}
}
