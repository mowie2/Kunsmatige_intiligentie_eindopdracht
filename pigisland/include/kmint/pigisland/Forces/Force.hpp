#pragma once
#include "kmint/math/vector2d.hpp"
#include "kmint/play.hpp"

class Force
{
	
public:
	virtual kmint::math::basic_vector2d<float> addForce(std::vector<kmint::play::actor*>& neighbours) = 0;
	Force(kmint::play::free_roaming_actor& actorin, kmint::math::basic_vector2d<float> forceIn, float factorIn) :factor(factorIn), actor(actorin)
	{
		force = forceIn;
	}
	virtual ~Force() = default;
	virtual std::unique_ptr<Force> clone() = 0;
	void Factor(float factorIn) { factor = (factor * factorIn) / 2; }
	float Factor() { return factor; }


protected:
	kmint::math::basic_vector2d<float> force;
	float factor;
	kmint::play::free_roaming_actor& actor;

};
