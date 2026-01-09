#include "enemy.h"
#include <SDL3/SDL_log.h>

void Enemy::take_turn()
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Monsters turn");
    body_parts.front().get()->move(Direction { 1, 0 });
};
