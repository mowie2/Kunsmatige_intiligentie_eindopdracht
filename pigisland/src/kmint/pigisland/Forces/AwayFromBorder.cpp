#include "kmint/pigisland/Forces/AwayFromBorder.hpp"
//#include "kmint/math/vector2d.hpp"
//#include "../../../../include/kmint/pigisland/Forces/AwayFromBorder.hpp"

kmint::math::basic_vector2d<float> AwayFromBorder::addForce(std::vector<kmint::play::actor*>& neighbours)
{
	
	for (const auto neighbour : neighbours)
	{
		const float xDif = neighbour->location().x() - actor.location().x();
		const float yDif = neighbour->location().y() - actor.location().y();
		kmint::math::vector2d vect(xDif, yDif);
		force += vect;
	}
	if (!neighbours.empty())
	{
		force /= neighbours.size();
		force = normalize(force);

		force *= factor;
		force = force * -20;
	}



	return  force;
}

std::unique_ptr<Force> AwayFromBorder::clone()
{
	return std::make_unique<AwayFromBorder>(actor, force, factor);
}

