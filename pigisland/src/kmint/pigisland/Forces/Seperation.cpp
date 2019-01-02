#include "kmint/pigisland/Forces/Seperation.hpp"

kmint::math::basic_vector2d<float> Seperation::addForce(std::vector<kmint::play::actor*>& neighbours)
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
		force = force * -1;
	}

	

	return  force;
}

std::unique_ptr<Force> Seperation::clone()
{
	return std::make_unique<Seperation>(actor, force, factor);
}

