#ifndef KMINT_PIGISLAND_PIG_HPP
#define KMINT_PIGISLAND_PIG_HPP

#include "kmint/play.hpp"
#include "Forces/Force.hpp"
#include "shark.hpp"

namespace kmint
{
	namespace pigisland
	{
		class pig : public play::free_roaming_actor
		{
		public:
			explicit pig(math::vector2d location);
			explicit pig(pig& gather, pig& mother, math::vector2d location);
			void newPig(pig& gather, pig& mother, math::vector2d location, pig& child);
			const ui::drawable& drawable() const override { return drawable_; }
			void move(math::vector2d delta) { location(location() + delta); }
			void act(delta_time dt) override;
			bool perceptive() const override { return true; }
			scalar range_of_perception() const override { return 30.0f; }
			void randomLocation(pig& pig);
			scalar radius()	const override;
			bool incorporeal() const override { return false; }
			bool must_draw() const override { return alive; }
			bool perceivable() const override { return alive; }
			time born;
			time death;
			time reachedBoat;
			math::vector2d calculate();
			std::vector<kmint::play::actor*> getNeighbours();
			std::vector<kmint::play::actor*> getShark();
			std::vector<kmint::play::actor*> getBoat();
			std::vector<kmint::play::actor*> getWall();
			void checkCollisions();
			void hasDied(const bool alive_) { alive = !alive_; }
			bool alive = true;
			void randomLocation();

			std::vector<std::unique_ptr<Force>> forces;
			play::image_drawable drawable_;

			math::vector2d velocity;
			float angle;
			float maxSpeed = 3;
		private:

		}; // namespace kmint
	}
}
#endif /* KMINT_PIGISLAND_PIG_HPP */
