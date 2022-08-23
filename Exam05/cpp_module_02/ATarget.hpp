#ifndef ATARGET_HPP
#define ATARGET_HPP

#include <string>
#include <iostream>
#include "ASpell.hpp"

using namespace std;

class ASpell;
class ATarget {
    private:
        string type;

        ATarget() {}
        ATarget& operator=(const ATarget&);
        ATarget(const ATarget&) {}

    public:
        ATarget(const string& type): type(type) {}
        virtual ~ATarget() {}

        const string& getType() const {
            return this->type;
        }

        virtual ATarget* clone() const = 0;

        void getHitBySpell(const ASpell&) const;
};

#endif