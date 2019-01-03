#pragma once
#include "State.h"
#include "kmint/pigisland/boat.hpp"
namespace  kmint
{
	namespace pigisland
	{
		class boat;
	}
}
class GrassIsland : public State
{
public:
	GrassIsland() = default;
	GrassIsland(kmint::pigisland::boat& boat_);
	~GrassIsland() = default;
	void Update(kmint::delta_time dt);
	kmint::pigisland::boat& _boat;
private:

};
