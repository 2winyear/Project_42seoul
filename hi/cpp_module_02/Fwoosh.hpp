#ifndef FWOOSH_HPP
#define FWOOSH_HPP

#include <iostream>
#include <string>
#include "ASpell.hpp"

using namespace std;

class Fwoosh : public ASpell {
    
    public:
        Fwoosh() : ASpell("Fwoosh", "Fwooshed") {}
        ~Fwoosh() {}
        virtual ASpell * clone () const {
            return new Fwoosh();
        }
};

#endif