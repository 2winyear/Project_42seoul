#ifndef ATARGET_HPP
#define ATARGET_HPP

#include <string>
#include <iostream>
#include "ASpell.hpp"

using namespace std;

class ATarget {
        string _type;

    public:
        ATarget();
        ATarget(string);
        ATarget(ATarget &);
        ATarget &operator=(ATarget &);
    
        virtual ~ATarget();
    
        void getHitBySpell(const ASpell &);
        const string &getType() const;
};

#endif