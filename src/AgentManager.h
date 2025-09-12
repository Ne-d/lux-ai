#pragma once

#include <map>
#include <string>

enum class UnitObjective : uint8_t;

namespace lux
{
	class Unit;
}

struct UnitData
{
	UnitObjective objective;
};

class AgentManager
{
public:
	AgentManager() = delete;
	static AgentManager* get();

	UnitData* getUnitData(const std::string& id);
	void addUnit(std::string& id);

private:
	static AgentManager* instance;
	std::map<std::string, UnitData> units;
};
