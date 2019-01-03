#pragma once


#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "resources.hpp"

namespace kmint {
	namespace pigisland {
		class BorderMarker : public play::free_roaming_actor {
		public:
			BorderMarker(math::vector2d location);
			bool must_draw() const override { return true; }
			const ui::drawable &drawable() const override { return drawable_; }
			bool incorporeal() const override { return false; }
			bool perceivable() const override { return true; }
			scalar radius() const override { return 30.0; }
			void act(delta_time dt) override;
			

		private:
			play::image_drawable drawable_;
		};

	} // namespace pigisland
} // namespace kmint

