#include "AgentManager.h"

#include <iostream>

UnitData* AgentManager::getUnitData(const std::string& id)
{
	return &units.at(id);
}


void AgentManager::addUnit(const std::string& id)
{
	const auto result = units.insert({id, UnitData{}});
}
