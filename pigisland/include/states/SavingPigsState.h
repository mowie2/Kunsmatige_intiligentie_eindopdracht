#pragma once
#include  "State.h"
#include "kmint/pigisland/boat.hpp"
namespace  kmint
{
	namespace pigisland
	{
		class boat;
	}
}
class SavingPigsState : public State
{
public:
	SavingPigsState() = default;
	SavingPigsState(kmint::pigisland::boat& boat_);
	~SavingPigsState() = default;
	void Update(kmint::delta_time dt);
	kmint::pigisland::boat& _boat;
private:
};