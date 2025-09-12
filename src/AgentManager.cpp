#include "AgentManager.h"

#include <iostream>

AgentManager* AgentManager::instance{};

AgentManager* AgentManager::get()
{
	return instance;
}


UnitData* AgentManager::getUnitData(const std::string& id)
{
	return &units.at(id);
}


void AgentManager::addUnit(std::string& id)
{
	auto result = units.insert(make_pair(id, UnitData{}));
	if (result.second)
		std::cerr << "Inserting new unit " << id << "\n";
	else
		std::cerr << "Unit " << id << " already exists\n";
}
