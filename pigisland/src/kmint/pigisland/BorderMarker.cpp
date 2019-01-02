#include "kmint/pigisland/BorderMarker.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include <cmath>



namespace kmint {
	namespace pigisland {

		namespace {

			math::vector2d random_vector() {
				auto x = random_scalar(100, 924);
				auto y = random_scalar(50, 728);
				return { x, y };
			}
		} // namespace

		BorderMarker::BorderMarker(math::vector2d location)
			: free_roaming_actor{ location }, drawable_{ *this, shark_image() }
		{
		}

		void BorderMarker::act(delta_time dt) {
			
		}

		
	} // namespace pigisland

} // namespace kmint
