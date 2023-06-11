#include "include/Equipment.h"

Equipment::Equipment(const std::string &name, char character, int x, int y,
                     const Stats &buff)
    : Item{name, character, x, y}, m_Buff{buff} {}
Item *Equipment::clone() const { return new Equipment(*this); }
bool Equipment::use(Hero *hero, std::string &outMsg)
{
    int type;
    switch (m_Character)
    {
    case '^':
        type = 0;
        break;
    case 'p':
        type = 1;
        break;
    case 'b':
        type = 2;
        break;
    case 'w':
        type = 3;
        break;
    case 'o':
        type = 4;
        break;
    default:
        throw "Unknown equipment type";
        break;
    }
    if (hero->equip(this, type))
    {
        outMsg = "Equipped " + m_Name;
        return true;
    }
    outMsg = "Cannot equip " + m_Name;
    return false;
}
std::string Equipment::printDescription() const
{
    std::stringstream res;
    res << "+ " << m_Buff.getHP() << " max HP\n"
        << "+ " << m_Buff.getMana() << " max mana\n"
        << "+ " << m_Buff.getStrength() << " strength\n"
        << "+ " << m_Buff.getMagic() << " magic\n"
        << "+ " << m_Buff.getArmor() << " armor\n"
        << "+ " << m_Buff.getResistance() << " resistance\n";
    return res.str();
}
const Stats &Equipment::getBuff() const { return m_Buff; }
