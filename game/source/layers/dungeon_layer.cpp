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

    Spritesheet spritesheet { "data/tiles.png", 128.0f, 232.0f };
    Spritesheet kenney_spritesheet { "data/kenney_tiny_town_tiles.png", 16, 16 };
    Spritesheet at_sign { "data/at_sign_01.png", 16.0f, 16.0f };

    // Adding player snake
    Sprite_specification snake_sprite_specification { spritesheet.get_sprite_specification(0, 4) }; // Default 0, 4
    Creature_builder<Snake> snake_builder { snake_sprite_specification };
    snake_builder.create_creature(3);
    snake = snake_builder.get_creature();
    snake.get()->set_position(Position { 20, 7 });
    turn_based_system.register_entity(snake);

    // Adding test enemy
    Sprite_specification enemy_sprite_specification { spritesheet.get_sprite_specification(5, 4) };
    Creature_builder<Enemy> enemy_builder { enemy_sprite_specification };
    enemy_builder.create_creature(1);
    enemy = enemy_builder.get_creature();
    enemy.get()->set_position(Position { 2, 1 });
    turn_based_system.register_entity(enemy);
}

void Dungeon_layer::on_update(float delta_time)
{
    turn_based_system.update(delta_time);
}

void Dungeon_layer::on_render()
{
    render_map_tiles();

    const Core::Sdl_manager::State& sdl_manager_state { Core::Game::get_instance().get_sdl_manager().get_state() };

    SDL_RenderPresent(sdl_manager_state.renderer);
}

void Dungeon_layer::render_map_tiles()
{
    const std::vector<std::shared_ptr<Tile>>& tiles { current_floor->get_tiles() };

    for (auto tile : tiles)
    {
        tile.get()->render();
    }
}

void Dungeon_layer::on_stop()
{
}

std::shared_ptr<Floor> Dungeon_layer::get_current_floor()
{
    return current_floor;
}
