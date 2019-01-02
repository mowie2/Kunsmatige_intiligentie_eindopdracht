#ifndef KMINT_PIGISLAND_PIG_HPP
#define KMINT_PIGISLAND_PIG_HPP

#include "kmint/play.hpp"
#include "Forces/Force.hpp"
#include "shark.hpp"

namespace kmint {
namespace pigisland {

class pig : public play::free_roaming_actor {
public:
  explicit pig(math::vector2d location);
  explicit pig(pig& father, pig& mother, math::vector2d location);
  const ui::drawable &drawable() const override { return drawable_; }
  void move(math::vector2d delta) { location(location() + delta); }
  void act(delta_time dt) override;
  bool perceptive() const override { return true; }
  scalar range_of_perception() const override { return 30.0f; }
  math::vector2d calculate();
  std::vector<kmint::play::actor*> getNeighbours();
  std::vector<kmint::play::actor*> getShark();
  std::vector<kmint::play::actor*> getBoat();
  std::vector<kmint::play::actor*> getWall();

private:
  play::image_drawable drawable_;
  math::vector2d velocity;
  float angle;
  std::vector<std::unique_ptr<Force>> forces;
  float maxSpeed = 3;
};

} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_PIG_HPP */
