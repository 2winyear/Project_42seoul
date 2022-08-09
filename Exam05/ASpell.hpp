#ifndef ASpell_HPP
#define ASpell_HPP

#include <string>
#include <iostream>
using namespace std;


class ASpell {
        string _name;
        string _effects;

    public:
        ASpell();
        ASpell(ASpell &);
        ASpell(const string &, const string &);
        ASpell &operator=(ASpell &);
        virtual ~ASpell();
    
        const string &getName() const;
        const string &getEffect() const;
};

#endif