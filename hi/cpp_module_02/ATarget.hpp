#ifndef ATARGET_HPP
#define ATARGET_HPP

#include <iostream>
#include <string>
#include "ASpell.hpp"

using namespace std;

class ASpell;
class ATarget {
    private:
        string type;

        ATarget();
        ATarget(const ATarget &);
        ATarget &operator=(const ATarget &);

    public:
        virtual ~ATarget() {}
        virtual ATarget * clone () const = 0;

        ATarget(const string& type);

        const string& getType () const;
        void getHitBySpell(const ASpell&) const;
};

#endif