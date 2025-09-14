#pragma once

#include <map>
#include <string>
#include <vector>

#include "Objective.h"
#include "lux/position.hpp"

// Forward declarations
enum class UnitObjective : uint8_t;

namespace lux
{
	class Unit;
}

/**
 * Struct that represents the objective data of a unit.
 * This is stored outside the unit to avoid modifying Lux's Unit class.
 */
struct UnitData
{
	// Current objective type
	UnitObjective objective = UnitObjective::COLLECT_FUEL;

	// Current target position
	lux::Position target;

	// If true, don't accept any new objective
	bool busy = false;
};

/**
 * A class that handles custom data and behaviour fur Lux units.
 */
class AgentManager
{
public:
	AgentManager() = default;

	/**
	 * Adds a unit to be tracked by AgentManager
	 * @param id The id of the unit to add.
	 */
	static void addUnit(const std::string& id);

	/**
	 * Remove all units from the list.
	 */
	static void clearUnits();

	/**
	 * Sets the pointer to the vector of Actions used by Lux to queue actions each turn.
	 * This makes it available statically from anywhere in the program.
	 * @param actionVector The address of Lux's actions vector.
	 */
	static void setActionVectorPointer(std::vector<std::string>* actionVector);

	/**
	 * Get the UnitData object associated with a unit.
	 * @param id The unit's id
	 * @return The UnitData of this unit
	 */
	static UnitData* getUnitData(const std::string& id);

	/**
	 * Sets the objective that the unit will follow, if the unit is not busy.
	 * @param unitId The unit's id
	 * @param objective The new objective
	 */
	static void setUnitObjective(std::string unitId, UnitObjective objective);

	/**
	 * Sets this unit to a non-busy state, indicating its current objective is finished,
	 * and it can accept a new one.
	 * @param unitId The unit's id
	 */
	static void setUnitObjectiveFinished(const std::string& unitId);

	/**
	 * Queue an action for this turn.
	 * @param action The action to queue.
	 */
	static void queueAction(const std::string& action);

private:
	/**
	 * A map that links each unit id to a UnitData object.
	 */
	static std::map<std::string, UnitData> units;

	/**
	 * A pointer to the Lux's list of actions to execute this turn.
	 */
	static std::vector<std::string>* actions;
};
