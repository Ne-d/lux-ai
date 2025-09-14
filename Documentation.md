# Code conventions
We use the code style already present in the Lux AI C++ Kit.

# Project Architecture
The Lux AI C++ Kit is located in the ``lux`` directory. We keep it unmodified.
Our own code is located in the ``src`` directory, except for the main.cpp file, which is in the root of the project.
It includes:
- All the code that handles units and the data we associate with them, in the AgentManager class.
- The code that defines the behaviour of worker units, based on their objective, in WorkerBehaviour.
- Various functions related to searching for cells on the map, in search.h and search.cpp.
- The overall structure of each turn of the game, in main.cpp.
