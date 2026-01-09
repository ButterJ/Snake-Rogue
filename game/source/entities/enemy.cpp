#include "enemy.h"
#include <SDL3/SDL_log.h>

Enemy::Enemy(Sprite_renderer& p_sprite_renderer, Sprite_specification p_sprite_specification)
    : sprite_renderer { p_sprite_renderer }, sprite_specification { p_sprite_specification }
{
    auto transform_component = std::make_shared<Transform_component>();
    auto sprite_component = std::make_shared<Sprite_component>(sprite_specification, transform_component);
    body_part = std::make_shared<Body_part>(sprite_component, transform_component);

    sprite_renderer.register_sprite_component(sprite_component);
}

void Enemy::take_turn()
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Monsters turn");
    body_part.get()->move(Direction { 1, 0 });
};
