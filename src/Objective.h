#pragma once
#include <cstdint>

/**
 * Enum that represents the different objectives a unit can have.
 */
enum class UnitObjective : uint8_t
{
	COLLECT_FUEL,
	COLLECT_WOOD,
	DEPOSIT,
	BUILD_CITY,
};

/**
 * Enum that represents the different objectives a city can have.
 */
enum class CityObjective : uint8_t
{
	BUILD_WORKERS,
	BUILD_CARTS,
	RESEARCH
};