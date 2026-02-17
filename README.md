# Snake Rogue
In Snake Rogue, a snake is cursed to satiate its never-ending hunger, having to thrive inside a jungle filled with ancient ruins and monsters, adapting to the dangers by growing and mutating its body.

Snake Rogue is a traditional roguelike that I am making with C++ and SDL3 to improve my programming and game design skills.
An overview over its design can be found at https://butterj.github.io/projects/snake-rogue/snake-rogue-overview.html
## Implemented systems and features
This section lists a few of the bigger systems and features that are implemented in the current version of the game.
### Turn-based system
The turn-based system processed all turn-based entities.
A turn-based entity has an action energy cost, current energy, and an energy regeneration rate. When processed, the entities current energy will increase by its energy regeneration rate, and if it has enough energy to take a turn, that energy is spent and they will start their turn.
If the turn-based entity is controlled by the player, the turn-based system will hold until the player's turn is finished. Otherwise, the entity will automatically decide on an action to do in its turn.
This system also allows the player to control multiple turn-based entities.
The energy system of the turn-based entities allow entities with different speeds. This can for example lead to the player being able to do two turns before a slow monster can do something.
### Creatures
Creatures are the base for the player character and monsters in the game.
A creature can be controlled by either the player or have simple game-controlled behaviour.
A creature can consist out of multiple body parts, with other body parts following the head. Creatures can move, attack, and eat, lose body parts, and regrow body parts.
### Stat system
Each creature has a number of different stats.
A stat has an initial value. The total value of a stat is modified by the stat modifiers applied to it.
Stat modifiers change a stat in three different ways:
- Flat (additive)
- Percent additive
- Percent multiplicative
There are also timed stat modifiers, which only last x amount of turns.
### Eating
Creatures can eat food. Eating food adds satiation to the creature. If a creature reaches maximum satiation, they spend it to regrow a lost body part. If a creature can not regrow a body part, they will gain an experience point which may lead them to level up and choose a mutation (the level-up system is not yet implemented).
Eating food may also apply a stat modifier to the creature. For example, when eating an apple the creature temporarily gains health regeneration.
