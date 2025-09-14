#pragma once

#include <map>
#include <string>
#include <vector>

#include "lux/position.hpp"


enum class UnitObjective : uint8_t;

namespace lux
{
	class Unit;
}

struct UnitData
{
	// Current objective type
	UnitObjective objective;

	// Current target position
	lux::Position target;

	// If true, don't accept any new objective
	bool busy;
};

class AgentManager
{
public:
	AgentManager() = default;
	static void addUnit(const std::string& id);
	static void clearUnits();
	static void setActionVectorPointer(std::vector<std::string>* actionVector);

	static UnitData* getUnitData(const std::string& id);
	static void setUnitObjective(std::string unitId, UnitObjective objective);
	static void setUnitObjectiveFinished(const std::string& unitId);

	static void addAction(const std::string& action);

private:
	static std::map<std::string, UnitData> units;
	static std::vector<std::string>* actions;
};
