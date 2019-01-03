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
class Forest : public State
{
public:
	Forest() = default;
	Forest(kmint::pigisland::boat& boat_);
	~Forest() = default;
	void Update(kmint::delta_time dt);
	kmint::pigisland::boat& _boat;
private:

};
