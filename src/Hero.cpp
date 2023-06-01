#include "include/Hero.h"

Hero::Hero (WINDOW * win, const std::string& name, char character, int x, int y, const Stats &stats)
: Character {win, name, character, x, y, stats}
{}