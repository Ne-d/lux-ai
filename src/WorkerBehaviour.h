#pragma once
#include "lux/game_objects.hpp"

enum class UnitObjective : unsigned char;

class WorkerBehaviour
{
public:
	/// Makes the given unit collect fuel from the nearest resource tile.
	static void collectFuel(const lux::Unit& unit, lux::Player player, const std::vector<lux::Cell*>& resourceTiles);

	/// Make the given unit deposit its fuel into the nearest city.
	static void deposit(const lux::Unit& unit, lux::Player player);

	/// Make the given unit try to build a city, next to the city it is closest to.
	static void buildCity(const lux::Unit& unit, lux::Player player, const lux::GameMap& gameMap);
};
