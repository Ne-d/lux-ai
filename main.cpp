#include "lux/kit.hpp"

#include <vector>
#include <set>

#include "AgentManager.h"
#include "Objective.h"
#include "WorkerBehaviour.h"

using namespace std;
using namespace lux;

int main()
{
  kit::Agent gameState = kit::Agent();
  // initialize
  gameState.initialize();

  while (true)
  {
    /** Do not edit! **/
    // wait for updates
    gameState.update();

    vector<string> actions = vector<string>();
    
    /** AI Code Goes Below! **/

    // Initialize data
    Player &player = gameState.players[gameState.id];
    Player &opponent = gameState.players[(gameState.id + 1) % 2];

    GameMap &gameMap = gameState.map;
    vector<Cell *> resourceTiles = vector<Cell *>();

    // Setup Action vector pointer in AgentManager
    AgentManager::setActionVectorPointer(&actions);

    // Find all resource tiles
    for (int y = 0; y < gameMap.height; y++)
    {
      for (int x = 0; x < gameMap.width; x++)
      {
        Cell *cell = gameMap.getCell(x, y);
        if (cell->hasResource())
          resourceTiles.push_back(cell);
      }
    }

    // Find all city tiles
    std::vector<CityTile*> cityTiles = std::vector<CityTile*>();
    for (int y = 0; y < gameMap.height; y++)
    {
      for (int x = 0; x < gameMap.width; x++)
      {
        Cell *cell = gameMap.getCell(x, y);
        if (cell->citytile != nullptr)
          cityTiles.push_back(cell->citytile);
      }
    }

    // Iterate over all our units and do something with them
    for (int i = 0; i < player.units.size(); i++)
    {
      const Unit unit = player.units[i];

      // Setup AgentManager
      AgentManager::clearUnits(); // To avoid accessing dead units (invalid references)
      AgentManager::addUnit(unit.id); // We rebuild the list every turn.

      // Compute unit objective, if that unit isn't busy (has no current objective)
      if (unit.isWorker() && !AgentManager::getUnitData(unit.id)->busy)
      {
        // If the unit can collect resources
        if (unit.getCargoSpaceLeft() > 0)
          AgentManager::setUnitObjective(unit.id, UnitObjective::COLLECT_FUEL);

        // If the unit has no space left
        else
        {
          // Choose randomly between building a new city and depositing resources for fuel
          if (rand() % 2 == 0)
            AgentManager::setUnitObjective(unit.id, UnitObjective::BUILD_CITY);
          else
            AgentManager::setUnitObjective(unit.id, UnitObjective::DEPOSIT);
        }
      }

      // Execute worker behaviour based on objective
      if (unit.isWorker() && unit.canAct())
      {
        switch (AgentManager::getUnitData(unit.id)->objective)
        {
        case UnitObjective::COLLECT_FUEL:
          WorkerBehaviour::collectFuel(unit, player, resourceTiles);
          break;

        case UnitObjective::DEPOSIT:
          WorkerBehaviour::deposit(unit, player);
          break;

        case UnitObjective::BUILD_CITY:
          WorkerBehaviour::buildCity(unit, player, gameMap);
          break;
        }
      }
    }

    // Iterate over all our cities
    for (std::pair<const string, City>& pair : player.cities)
    {
      City& city = pair.second;

      // Iterate over each CityTile of the city
      for (CityTile& cityTile : city.citytiles)
      {
        // If we can have a new unit, build one
        if (player.units.size() < player.cityTileCount)
          actions.push_back(cityTile.buildWorker());
        else
          // If we have enough fuel to survive a full night, do some research.
          if (cityTile.canAct() && city.fuel > city.getLightUpkeep() * 10) // TODO: Ugly magic number
            actions.push_back(cityTile.research());
      }
    }

    /** AI Code Goes Above! **/

    /** Do not edit! **/
    for (int i = 0; i < actions.size(); i++)
    {
      if (i != 0)
        cout << ",";
      cout << actions[i];
    }
    cout << endl;
    // end turn
    gameState.end_turn();
  }

  return 0;
}
