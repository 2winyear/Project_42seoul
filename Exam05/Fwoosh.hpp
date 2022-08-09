#ifndef ATARGET_HPP
#define ATARGET_HPP

#include <string>
#include <iostream>
#include "ASpell.hpp"

using namespace std;

class Fwoosh {
        string _type;

    public:
        Fwoosh();
        Fwoosh(string);
        Fwoosh(Fwoosh &);
        Fwoosh &operator=(Fwoosh &);
    
        virtual ~Fwoosh();
    
        void getHitBySpell(const ASpell &);
        const string &getType() const;
};

#endif