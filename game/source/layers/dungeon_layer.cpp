#include "dungeon_layer.h"

#include "apple.h"
#include "position.h"
#include "sprite_specification.h"

#include <SDL3_image/SDL_image.h>

#include <memory>

// TODO: Replace test functionality after prototype
void Dungeon_layer::on_start()
{
    m_current_floor = m_premade_floor_generator->generate_floor(20, 40);

    Spritesheet snake_spritesheet { "data/body_part_snake.png", 8.0f, 8.0f };
    Spritesheet enemy_spritesheet { "data/body_part_enemy.png", 16.0f, 16.0f };
    Spritesheet apple_spritesheet { "data/apple.png", 16.0f, 16.0f };

    Sprite_specification snake_sprite_specification { snake_spritesheet.get_sprite_specification(0, 0) };
    m_snake = std::make_shared<Player_snake>(3, snake_sprite_specification);
    m_snake.get()->set_position(Position { 20, 7 });
    m_turn_based_system.register_entity(m_snake);

    // Adding test enemies
    Sprite_specification enemy_sprite_specification { enemy_spritesheet.get_sprite_specification(0, 0) };

    m_enemy_01 = std::make_shared<Simple_enemy>(1, enemy_sprite_specification);
    m_enemy_01.get()->set_position(Position { 2, 14 });
    m_turn_based_system.register_entity(m_enemy_01);

    m_enemy_02 = std::make_shared<Simple_enemy>(1, enemy_sprite_specification);
    m_enemy_02.get()->set_position(Position { 32, 2 });
    m_turn_based_system.register_entity(m_enemy_02);

    // Adding test food
    Sprite_specification apple_sprite_specification { apple_spritesheet.get_sprite_specification(0, 0) };

    Position food_position { 10, 6 };
    std::shared_ptr<Food> apple_01 { std::make_shared<Apple>(food_position, apple_sprite_specification, 50) };
    get_current_floor()->get_tile_at_position(food_position)->add_game_object(Tile::Occupant_type::food, apple_01);

    Position food_position_2 { 30, 12 };
    std::shared_ptr<Food> apple_02 { std::make_shared<Apple>(food_position_2, apple_sprite_specification, 50) };
    get_current_floor()->get_tile_at_position(food_position_2)->add_game_object(Tile::Occupant_type::food, apple_02);
}

void Dungeon_layer::on_update(float delta_time)
{
    m_turn_based_system.update(delta_time);
}

void Dungeon_layer::on_render()
{
    render_map_tiles();

    const Core::Sdl_manager::State& sdl_manager_state { Core::Game::get_instance().get_sdl_manager().get_state() };

    SDL_RenderPresent(sdl_manager_state.renderer);
}

void Dungeon_layer::render_map_tiles()
{
    const std::vector<std::shared_ptr<Tile>>& tiles { m_current_floor->get_tiles() };

    for (const auto& tile : tiles)
    {
        tile.get()->render();
    }
}

void Dungeon_layer::on_stop()
{
}

std::shared_ptr<Floor> Dungeon_layer::get_current_floor()
{
    return m_current_floor;
}
