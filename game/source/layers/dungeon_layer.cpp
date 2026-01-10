#include "dungeon_layer.h"

#include "creature_builder.h"
#include "player_controlled_entity.h"
#include "position.h"
#include "sprite_specification.h"

#include <SDL3_image/SDL_image.h>
#include <memory>

void Dungeon_layer::on_start() // TODO: Replace test functionality
{
    current_floor = premade_floor_generator->generate_floor(14, 50);

    // Adding player snake
    Creature_builder<Snake> snake_builder {};
    snake_builder.create_creature(3);
    snake = snake_builder.get_creature();
    snake.get()->set_position(Position { 5, 7 });
    turn_based_system.register_entity(snake);

    // Adding test enemy
    Creature_builder<Enemy> enemy_builder {};
    enemy_builder.create_creature(1);
    enemy = enemy_builder.get_creature();
    enemy.get()->set_position(Position { 2, 1 });
    turn_based_system.register_entity(enemy);
}

void Dungeon_layer::on_update(float delta_time)
{
    turn_based_system.update(delta_time);
}

void Dungeon_layer::on_render() // TODO: Remove test functionality
{
    const Core::Sdl_manager::State& sdl_manager_state { Core::Game::get_instance().get_sdl_manager().get_state() };

    SDL_SetRenderDrawColor(sdl_manager_state.renderer, 200, 200, 200, 255);
    SDL_RenderClear(sdl_manager_state.renderer);

    render_map_tiles();

    snake.get()->render();
    enemy.get()->render();

    SDL_RenderPresent(sdl_manager_state.renderer);
}

void Dungeon_layer::render_map_tiles()
{
    const std::vector<Tile>& tiles { current_floor->get_tiles() };

    for (auto tile : tiles)
    {
        tile.render();
    }
}

void Dungeon_layer::on_stop()
{
}

std::shared_ptr<Floor> Dungeon_layer::get_current_floor()
{
    return current_floor;
}
