#ifndef FIREBALL_HPP
#define FIREBALL_HPP

#include <iostream>
#include <string>
#include "ASpell.hpp"

using namespace std;

class Fireball : public ASpell {
    
    public:
        Fireball() : ASpell("Fireball", "burnt to a crisp") {}
        ~Fireball() {}
        virtual ASpell * clone () const {
            return new Fireball();
        }
};

#endif