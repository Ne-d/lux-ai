#pragma once
#include "lux/game_objects.hpp"

enum class UnitObjective : unsigned char;

class WorkerBehaviour
{
public:
	static void collectFuel(const lux::Unit& unit, lux::Player player, const std::vector<lux::Cell*>& resourceTiles);
	static void deposit(const lux::Unit& unit, lux::Player player);
	static void collectWood();
	static void buildCity(const lux::Unit& unit, lux::Player player, const lux::GameMap& gameMap);
};
