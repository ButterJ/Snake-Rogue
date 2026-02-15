#pragma once

#include "input_controller.h"

#include "action_result.h"
#include "body_part.h"
#include "direction.h"

#include <memory>
#include <vector>

class Simple_enemy_input_controller : public Input_controller
{
  public:
    Simple_enemy_input_controller(std::vector<std::shared_ptr<Body_part>>& enemy_body_parts);

    void start_deciding_on_action() override;

  private:
    Action_result move_towards_weighted_random_direction(const std::vector<Direction>& occupied_directions);

    Direction m_last_move_direction { Direction::Zero };

    std::vector<std::shared_ptr<Body_part>>& m_enemy_body_parts;
};
