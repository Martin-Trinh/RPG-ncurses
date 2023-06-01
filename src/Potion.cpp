#include "include/Potion.h"

Potion::Potion(const std::string& name, char character, int x, int y,
                 int hp, int mana, int exp)
:Item{name, character, x, y}, m_HP{hp}, m_Mana{mana}, m_Exp{exp}{}
bool Potion:: use(Hero & hero){
    return true;
}