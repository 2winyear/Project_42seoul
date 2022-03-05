#include "HumanA.hpp"
#include "HumanB.hpp"
#include "Weapon.hpp"

/*
    질문하고 싶은 점.
    1. HumanA에서 HumanA 부분에서 &weapon인데,
    HumanB에서는 *weapon인걸까? 과제에서 말하고 싶은게 뭔지 모르겠다. 
*/
int main()
{
  {
    Weapon club = Weapon("crude spiked club");
    HumanA bob("Bob", club);
    bob.attack();
    club.setType("some other type of club");
    bob.attack();
  }
  {
    Weapon club = Weapon("crude spiked club");
    HumanB jim("Jim");
    jim.setWeapon(club);
    jim.attack();
    club.setType("some other type of club");
    jim.attack();
  }
}