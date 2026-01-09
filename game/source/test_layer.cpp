#include "test_layer.h"
#include "sprite_specification.h"

#include <SDL3_image/SDL_image.h>

void Test_layer::on_start()
{
    // Adding player snake
    Sprite_specification sprite_specification { brogue_tiles.get_sprite_specification(0, 4) };
    snake = std::make_unique<Snake>(3, sprite_renderer, sprite_specification);
    turn_based_system.register_entity(snake);

    // Adding enemy
    Sprite_specification sprite_specification_enemy { brogue_tiles.get_sprite_specification(5, 4) };
    enemy = std::make_unique<Enemy>(sprite_renderer, sprite_specification_enemy);
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
    sprite_renderer.render_sprites();

    SDL_RenderPresent(sdl_manager_state.renderer);
}

void Test_layer::on_stop()
{
    sprite_renderer.release_sprite_component(test_sprite_component);
}
