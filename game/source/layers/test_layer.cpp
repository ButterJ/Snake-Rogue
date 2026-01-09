#include "test_layer.h"

#include "creature_builder.h"
#include "player_controlled_entity.h"
#include "sprite_specification.h"

#include <SDL3_image/SDL_image.h>
#include <memory>

void Test_layer::on_start()
{
    // Adding player snake
    Creature_builder<Snake> snake_builder {};
    snake_builder.create_creature(3);
    snake = snake_builder.get_creature();
    turn_based_system.register_entity(snake);

    Creature_builder<Enemy> enemy_builder {};
    enemy_builder.create_creature(1);
    enemy = enemy_builder.get_creature();
    turn_based_system.register_entity(enemy);
}

void Test_layer::on_update(float delta_time)
{
    turn_based_system.update(delta_time);
}

void Test_layer::on_render()
{
    SDL_SetRenderDrawColor(sdl_manager_state.renderer, 200, 200, 200, 255);
    SDL_RenderClear(sdl_manager_state.renderer);

    snake.get()->render();
    enemy.get()->render();
    // sprite_renderer.render_sprites();

    SDL_RenderPresent(sdl_manager_state.renderer);
}

void Test_layer::on_stop()
{
}
