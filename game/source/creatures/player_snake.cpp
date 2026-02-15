#include "player_snake.h"

#include "player_input_controller.h"

Player_snake::Player_snake(int number_of_body_parts, const Sprite_specification& sprite_specification)
    : Creature(number_of_body_parts, sprite_specification, std::make_shared<Player_input_controller>())
{
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
