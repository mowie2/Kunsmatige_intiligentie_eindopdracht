#include "kmint/pigisland/Forces/Alignment.hpp"

kmint::math::basic_vector2d<float> Alignment::addForce(std::vector<kmint::play::actor*>& neighbours)
{
	for (const auto neighbour : neighbours)
	{
		const float xDif = neighbour->heading().x() - actor.heading().x();
		const float yDif = neighbour->heading().y() - actor.heading().y();
		kmint::math::vector2d vector(xDif, yDif);
		force += vector;
	}
	if(!neighbours.empty())
	{
		force /= neighbours.size();
		//force = normalize(force);

		force *= factor;
	}
	
	return  force;
}

std::unique_ptr<Force> Alignment::clone()
{
	return std::make_unique<Alignment>(actor, force, factor);
}

