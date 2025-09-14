#include "AgentManager.h"

std::map<std::string, UnitData> AgentManager::units;
std::vector<std::string>* AgentManager::actions;


UnitData* AgentManager::getUnitData(const std::string& id)
{
	return &units.at(id);
}


void AgentManager::addUnit(const std::string& id)
{
	const auto result = units.insert({id, UnitData{}});
}


void AgentManager::clearUnits()
{
	units.clear();
}


void AgentManager::setActionVectorPointer(std::vector<std::string>* actionVector)
{
	actions = actionVector;
}


void AgentManager::setUnitObjective(std::string unitId, UnitObjective objective)
{
	if (getUnitData(unitId)->busy)
		return;

	getUnitData(unitId)->objective = objective;
	getUnitData(unitId)->busy = true;
}


void AgentManager::setUnitObjectiveFinished(const std::string& unitId)
{
	getUnitData(unitId)->busy = false;
}


void AgentManager::addAction(const std::string& action)
{
	actions->push_back(action);
}
