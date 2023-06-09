#include "include/Potion.h"

Potion::Potion(const std::string& name, char character,int x, int y,
                 int hp, int mana, int exp)
:Item{name, character ,x, y}, m_HP{hp}, m_Mana{mana}, m_Exp{exp}{}

bool Potion::use(Hero* hero, std::string& outMsg){
    std::stringstream res;
    if(m_HP != 0){
        hero->increaseHP(m_HP);
        res << "+ " << m_HP << "HP\t";
    }
    if(m_Mana != 0){
        hero->increaseMana(m_Mana);
        res << "+ " << m_Mana << "Mana\t";
    }
    if(m_Exp != 0){
        hero->gainExp(m_Exp);
        res << "+ " << m_Exp << "Exp\t";
    }
    outMsg = res.str();
    return true;
}
std::string Potion::printDescription() const
{
    std::stringstream res;
    res << "+ " << m_HP << " max HP\n"
        << "+ " << m_Mana << " max mana\n"
        << "+ " << m_Exp << " Exp\n";
    return res.str();
}
std::string Potion::toData()const{
    std::stringstream res;
    res << Item::toData() 
        << m_HP << ',' << m_Mana << ',' << m_Exp;
    return res.str();
}