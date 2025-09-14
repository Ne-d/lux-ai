#pragma once
#include <cstdint>

enum class UnitObjective : uint8_t
{
	COLLECT_FUEL,
	COLLECT_WOOD,
	DEPOSIT,
	BUILD_CITY,
};

enum class CityObjective : uint8_t
{
	BUILD_WORKERS,
	BUILD_CARTS,
	RESEARCH
};