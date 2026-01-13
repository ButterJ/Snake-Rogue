#include "enemy.h"
#include <SDL3/SDL_log.h>

void Enemy::take_turn()
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Monsters turn");
    move(Direction { 1, 0 });
}
