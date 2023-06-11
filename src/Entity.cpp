#include "include/Entity.h"

Entity::Entity(const std::string& name, char character, int x, int y):
m_Name{name}, m_Character{character}, m_Pos{x, y}{}

Position Entity::getPos()const{return m_Pos;}
const std::string& Entity::getName()const{return m_Name;}
char Entity::getCharacter()const{return m_Character;}

void Entity::setPosition(int x, int y){
    m_Pos.m_X = x;
    m_Pos.m_Y = y;
}
void Entity::displayEntity(WINDOW* win, int margin)const{
    mvwaddch(win, m_Pos.m_Y + margin, m_Pos.m_X + margin, m_Character);
}