#include "include/Equipment.h"

Equipment::Equipment(const std::string& name, char character, int x, int y, 
                const Stats& buff)
: Item{name, character,x, y}, m_Buff{buff}{}
bool Equipment::use(Hero* hero, std::string& outMsg){
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
    if(hero->equip(this, type)){
        outMsg = "Equipped " + m_Name;
        return true;
    }
    outMsg = "Cannot equip " + m_Name;
    return false;
}
std::string Equipment::toData()const{
    std::stringstream res;
    res << Item::toData() << m_Buff.toData() ;
    return res.str();
}
const Stats& Equipment::getBuff() const{return m_Buff;}
