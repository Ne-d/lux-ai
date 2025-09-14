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
	UnitObjective objective;
	lux::Position target;
};

class AgentManager
{
public:
	AgentManager() = default;

	UnitData* getUnitData(const std::string& id);
	void addUnit(const std::string& id);

	static std::vector<std::string>* actions;
	static void addAction(const std::string& action);

private:
	std::map<std::string, UnitData> units;
};
