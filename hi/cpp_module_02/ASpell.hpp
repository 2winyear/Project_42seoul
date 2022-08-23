#ifndef ASPELL_HPP
#define ASPELL_HPP

#include <iostream>
#include <string>
#include "ATarget.hpp"

using namespace std;

class ATarget;
class ASpell {
    private:
        string name;
        string effects;

        ASpell();
        ASpell(const ASpell &);
        ASpell &operator=(const ASpell &);

    public:
        virtual ~ASpell() {}
        virtual ASpell * clone () const = 0;

        ASpell(const string& name, const string& effects);
        const string & getName () const ;
        const string & getEffects () const ;
        void launch(const ATarget&) const;
};

#endif