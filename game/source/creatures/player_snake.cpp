#include "player_snake.h"

#include "spritesheet.h"

Player_snake::Player_snake(int number_of_body_parts)
    : Creature(number_of_body_parts, create_sprite_specification(), create_input_controller())
{
    m_stats.attack_damage.set_base_value(20.0f);
}

void Player_snake::die()
{
    Turn_based_entity::die();

    // TODO: The following needs to be replaced with actual death handling. It is just for the prototype.
    SDL_Event quit_event {};
    quit_event.type = SDL_EVENT_QUIT;
    SDL_PushEvent(&quit_event);

    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "You died", "You have died. Try again by starting the game again", NULL);
}

Sprite_specification Player_snake::create_sprite_specification()
{
    static Spritesheet spritesheet { "data/body_part_snake.png", 8.0f, 8.0f };
    return spritesheet.get_sprite_specification(0, 0);
}

std::shared_ptr<Player_input_controller> Player_snake::create_input_controller()
{
    return std::make_shared<Player_input_controller>();
}
