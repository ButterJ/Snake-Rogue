#include "dungeon_layer.h"

#include "food.h"
#include "player_controlled_entity.h"
#include "position.h"
#include "sprite_specification.h"

#include <SDL3_image/SDL_image.h>
#include <memory>

void Dungeon_layer::on_start() // TODO: Replace test functionality
{
    current_floor = premade_floor_generator->generate_floor(20, 40);

    Spritesheet snake_spritesheet { "data/body_part_snake.png", 16.0f, 16.0f };
    Spritesheet enemy_spritesheet { "data/body_part_enemy.png", 16.0f, 16.0f };

    // Adding player snake
    Sprite_specification snake_sprite_specification { snake_spritesheet.get_sprite_specification(0, 0) };
    snake = std::make_shared<Snake>(3, snake_sprite_specification);
    snake.get()->set_position(Position { 20, 7 });
    turn_based_system.register_entity(snake);

    // Adding test enemy
    Sprite_specification enemy_sprite_specification { enemy_spritesheet.get_sprite_specification(0, 0) };
    enemy = std::make_shared<Enemy>(1, enemy_sprite_specification);
    enemy.get()->set_position(Position { 2, 1 });
    turn_based_system.register_entity(enemy);

    // Adding test food
    Position food_position { 10, 6 };
    std::shared_ptr<Food> test_food { std::make_shared<Food>(food_position, enemy_sprite_specification, 50) };
    get_current_floor()->get_tile_at_position(food_position)->add_food(test_food);

    Position food_position_2 { 30, 12 };
    std::shared_ptr<Food> test_food_2 { std::make_shared<Food>(food_position_2, enemy_sprite_specification, 50) };
    get_current_floor()->get_tile_at_position(food_position_2)->add_food(test_food_2);
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
