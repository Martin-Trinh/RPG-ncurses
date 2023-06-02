#include "include/Equipment.h"

Equipment::Equipment(WINDOW* win, const std::string& name, char character, int x, int y, 
                const Stats& buff, int durability)
: Item{win, name,character, x, y}, m_Buff{buff}, m_Durability{durability}{}
bool Equipment::use(Hero& hero){
    return true;
}
std::string Equipment::toData()const{
    std::stringstream res;
    res << Item::toData() << m_Buff.toData() << ',' << m_Durability;
    return res.str();
}