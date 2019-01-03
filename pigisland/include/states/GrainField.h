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
class GrainField : public State
{
public:
	GrainField() = default;
	GrainField(kmint::pigisland::boat& boat_);
	~GrainField() = default;
	void Update(kmint::delta_time dt);
	kmint::pigisland::boat& _boat;
private:

};
