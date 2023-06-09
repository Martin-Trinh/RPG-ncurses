#include "include/Key.h"

Key::Key(const std::string& name, char character, int x, int y, std::vector<Gate*>* gates)
:Item{name, character ,x, y}, m_Gates{gates}{}
bool Key::use(Hero* hero, std::string& outMsg){
    auto it = std::find_if(m_Gates->begin(), m_Gates->end(), [hero](Gate* gate){
        return gate->getPos() == hero->getPos();
    });
    if(it != m_Gates->end()){
        (*it)->open();
        outMsg = "Gate opened";
        return true;
    }
    outMsg = "You are not at the gate";
    return false;
}
std::string Key::printDescription()const {
    std::stringstream res;
    res << "Can be used to open gate(-) on map\n";
    return res.str();
}
std::string Key:: toData() const{
    std::stringstream res;
    res << Item::toData();
    return res.str();
}