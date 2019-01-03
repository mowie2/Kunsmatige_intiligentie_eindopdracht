#ifndef KMINT_PIGISLAND_PIG_HPP
#define KMINT_PIGISLAND_PIG_HPP

#include "kmint/play.hpp"

namespace kmint
{
	namespace pigisland
	{
		class pig : public play::free_roaming_actor
		{
		public:
			explicit pig(math::vector2d location);
			const ui::drawable& drawable() const override { return drawable_; }
			void move(math::vector2d delta) { location(location() + delta); }
			void act(delta_time dt) override;
			bool perceptive() const override { return true; }
			scalar range_of_perception() const override { return 30.0f; }

			scalar radius()	const override;
			bool incorporeal() const override { return false; }
			bool must_draw() const override { return alive; }
			bool perceivable() const override { return alive; }
			time born;
			time death;
			void hasDied(const bool alive_) { alive = !alive_; }
		private:
			play::image_drawable drawable_;
			bool alive = true;
		};
	} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_PIG_HPP */
