#ifndef Polymorph_HPP
#define Polymorph_HPP

#include <iostream>
#include <string>
#include "ASpell.hpp"

using namespace std;

class Polymorph : public ASpell {
    
    public:
        Polymorph() : ASpell("Polymorph", "turned into a critter") {}
        ~Polymorph() {}
        virtual ASpell * clone () const {
            return new Polymorph();
        }
};

#endif