#include "AgentManager.h"

#include <iostream>

std::vector<std::string>* AgentManager::actions;

UnitData* AgentManager::getUnitData(const std::string& id)
{
	return &units.at(id);
}


void AgentManager::addUnit(const std::string& id)
{
	const auto result = units.insert({id, UnitData{}});
}


void AgentManager::addAction(const std::string& action)
{
	actions->push_back(action);
}
