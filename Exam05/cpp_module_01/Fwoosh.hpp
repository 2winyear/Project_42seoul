#ifndef FWOOSH_HPP
#define FWOOSH_HPP

#include <string>
#include <iostream>
#include "ASpell.hpp"

using namespace std;

class Fwoosh : public ASpell {

    public:
        Fwoosh() : ASpell("Fwoosh", "fwooshed") {}
        ~Fwoosh() {}
        virtual ASpell* clone() const {
            return new Fwoosh();
        }
};

#endif