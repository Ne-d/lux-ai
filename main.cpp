#include "lux/kit.hpp"

#include <vector>
#include <set>

#include "AgentManager.h"
#include "search.h"

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
      Unit unit = player.units[i];

      // Setup AgentManager
      AgentManager::get()->addUnit(unit.id);

      // If the unit is a worker
      if (unit.isWorker() && unit.canAct())
      {
        // If the unit can collect resources
        if (unit.getCargoSpaceLeft() > 0)
        {
          // Find the closest resource tile
          Cell *closestResourceTile = findClosestResourceTile(unit, player, resourceTiles);
          if (closestResourceTile != nullptr)
          {
            auto dir = unit.pos.directionTo(closestResourceTile->pos);
            actions.push_back(unit.move(dir));
          }
        }
        // If the unit has no space left
        else
        {
          // And we have cities available
          if (player.cities.size() > 0)
          {
            // Go to the nearest city
            const CityTile *closestCityTile = findClosestCityTile(unit, player);
            if (closestCityTile != nullptr)
            {
              if (closestCityTile->pos.distanceTo(unit.pos) <= 1 && unit.canBuild(gameMap) && unit.canAct())
              {
                actions.push_back(unit.move(DIRECTIONS::WEST));
                actions.push_back(unit.buildCity());
              }

              auto dir = unit.pos.directionTo(closestCityTile->pos);
              actions.push_back(unit.move(dir));
            }
          }
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
        // If we have enough fuel to survive a full night, do some research.
        if (cityTile.canAct() && city.fuel > city.getLightUpkeep() * 10) // TODO: Ugly magic number
          actions.push_back(cityTile.research());
      }
    }

    // you can add debug annotations using the methods of the Annotate class.
    // actions.push_back(Annotate::circle(0, 0));

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
