#ifndef ASPELL_HPP
#define ASPELL_HPP

#include <string>
#include <iostream>
#include "ATarget.hpp"

using namespace std;

class ATarget;
class ASpell {
    private:
        string name;
        string effects;

        ASpell() {}
        ASpell& operator=(const ASpell&);
        ASpell(const ASpell&) {}

    public:
        ASpell(const string& name, const string& effects): name(name), effects(effects) {}
        const string& getName() const {
            return this->name;
        }
        const string& getEffects() const {
            return this->effects;
        }
        virtual ~ASpell() {}
        virtual ASpell* clone() const = 0;

        void launch(const ATarget &);
};

#endif