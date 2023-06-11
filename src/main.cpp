 
#include "include/Game.h"
#include "include/GameConfig.h"
int main()
{
    Game game;
    game.displayMenu();
    // try{
    //     GameConfig config("config1");
    //     Hero* hero1 = config.getHero("Warrior");
    //     Hero* hero2 = config.getHero("Wizard");
    //     Hero* hero3 = config.getHero("Archer");
    //     std::cout << (hero1->getName()) << std::endl;
    //     std::cout << (hero2->getName()) << std::endl;
    //     std::cout << (hero3->getName()) << std::endl;
    // }catch(const char* e){
    //     std::cout << e << std::endl;
    // }
    // catch(const std::string &e){
    //     std::cout << e << std::endl;
    // }

    return 0;
}