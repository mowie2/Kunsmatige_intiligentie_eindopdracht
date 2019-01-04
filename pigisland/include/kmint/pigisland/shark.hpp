#ifndef KMINT_PIGISLAND_SHARK_HPP
#define KMINT_PIGISLAND_SHARK_HPP

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "states/State.h"
#include <map>
#include "Astar.h"
#include "pig.hpp"

namespace kmint {
	namespace pigisland {
		class pig;
	}
}
namespace kmint
{
	namespace pigisland
	{
		class shark : public play::map_bound_actor
		{
		public:

			enum STATE_NAMES
			{
				WANDER_STATE,
				ATTACK_STATE,
				REST_STATE,
				SCARED_STATE
			};

			shark(map::map_graph& g, std::vector<pig*> p);
			std::vector<pig*> pigs;
			ui::drawable const& drawable() const override { return drawable_; }
			bool incorporeal() const override { return false; }
			scalar radius() const override { return 16.0; }
			void act(delta_time dt) override;
			void SetState(STATE_NAMES state);
			void setPathTo(const kmint::map::map_node& target);
			void goToRestingPlace();
			const std::vector<const kmint::map::map_node*> shark::get_path() const;
			map::map_node const* resting_place_;
			int stepsTaken = 0;
			scalar range_of_perception() const override;
			bool perceptive() const override;



		private:
			play::image_drawable drawable_;
			map::map_graph* map_;

			std::vector<const kmint::map::map_node*> path;
			Astar astar;
			void RegisterStates();
			State* currentState;
			std::map<STATE_NAMES, std::unique_ptr<State>> States;
		};
	} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_SHARK_HPP */
