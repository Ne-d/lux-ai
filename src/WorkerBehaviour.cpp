#include "WorkerBehaviour.h"

#include "AgentManager.h"
#include "search.h"
#include "lux/annotate.hpp"

namespace lux
{
	class Cell;
}


void WorkerBehaviour::collectFuel(const lux::Unit& unit, lux::Player player, const std::vector<lux::Cell*>& resourceTiles)
{
	// Go to the closest resource tile
	const lux::Cell *closestResourceTile = findClosestResourceTile(unit, player, resourceTiles);
	if (closestResourceTile != nullptr)
	{
		const auto dir = unit.pos.directionTo(closestResourceTile->pos);
		AgentManager::queueAction(unit.move(dir));
	}
	else
		AgentManager::setUnitObjectiveFinished(unit.id);

	// Once cargo is filled, get a new objective.
	if (unit.getCargoSpaceLeft() < 1)
		AgentManager::setUnitObjectiveFinished(unit.id);
}


void WorkerBehaviour::deposit(const lux::Unit& unit, lux::Player player)
{
	// Go to the nearest city
	const lux::CityTile *closestCityTile = findClosestCityTile(unit, player);
	if (closestCityTile != nullptr)
	{
		const auto dir = unit.pos.directionTo(closestCityTile->pos);
		AgentManager::queueAction(unit.move(dir));
	}

	// Once cargo is empty, get a new objective
	if (unit.getCargoSpaceLeft() > 99)
		AgentManager::setUnitObjectiveFinished(unit.id);
}


void WorkerBehaviour::buildCity(const lux::Unit& unit, lux::Player player, const lux::GameMap& gameMap)
{
	// If we don't have enough resources to build a city, get a new objective.
	if (unit.getCargoSpaceLeft() > 0)
		AgentManager::setUnitObjectiveFinished(unit.id);

	// Find the cell to build on
	const lux::CityTile *closestCityTile = findClosestCityTile(unit, player);
	const lux::City closestCity = player.cities.at(closestCityTile->cityid);
	const lux::Cell* cellToBuild = findTileToBuild(closestCity, gameMap);
	AgentManager::queueAction(lux::Annotate::x(cellToBuild->pos.x, cellToBuild->pos.y));

	// If we are not on the cell yet, move to it, avoiding existing city tiles.
	if (cellToBuild->pos.distanceTo(unit.pos) > 0)
	{
		lux::DIRECTIONS direction = unit.pos.directionTo(cellToBuild->pos);
		const lux::Position nextPosition = unit.pos.translate(direction, 1);

		// If we are about to move to a city
		if (gameMap.getCellByPos(nextPosition)->citytile != nullptr)
			direction = rotateDirection(direction, (rand() % 2) == 0 ? 1 : 3);

		AgentManager::queueAction(unit.move(direction));
	}
	else
	{
		AgentManager::queueAction(unit.buildCity());
	}
}
