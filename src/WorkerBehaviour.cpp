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
	const lux::Cell *closestResourceTile = findClosestResourceTile(unit, player, resourceTiles);

	if (closestResourceTile != nullptr)
	{
		const auto dir = unit.pos.directionTo(closestResourceTile->pos);
		AgentManager::addAction(unit.move(dir));
	}

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
		AgentManager::addAction(unit.move(dir));
	}

	if (unit.cargo.wood == 0 && unit.cargo.coal == 0 && unit.cargo.uranium == 0)
		AgentManager::setUnitObjectiveFinished(unit.id);
}


void WorkerBehaviour::collectWood()
{
}


void WorkerBehaviour::buildCity(const lux::Unit& unit, lux::Player player, const lux::GameMap& gameMap)
{
	if (unit.cargo.wood < 100 && unit.cargo.coal < 100 && unit.cargo.uranium < 100)
		AgentManager::setUnitObjectiveFinished(unit.id);

	const lux::CityTile *closestCityTile = findClosestCityTile(unit, player);
	const lux::City closestCity = player.cities.at(closestCityTile->cityid);

	const lux::Cell* tileToBuild = findTileToBuild(closestCity, gameMap);
	AgentManager::addAction(lux::Annotate::x(tileToBuild->pos.x, tileToBuild->pos.y));

	if (tileToBuild->pos.distanceTo(unit.pos) > 0)
	{
		lux::DIRECTIONS direction = unit.pos.directionTo(tileToBuild->pos);
		const lux::Position nextPosition = unit.pos.translate(direction, 1);

		// If we are about to move to a city
		if (gameMap.getCellByPos(nextPosition)->citytile != nullptr)
			direction = rotateDirection(direction, (rand() % 2) == 0 ? 1 : 3);

		AgentManager::addAction(unit.move(direction));
	}
	else
	{
		AgentManager::addAction(unit.buildCity());
	}
}
