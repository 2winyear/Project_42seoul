#ifndef DUMMY_HPP
#define DUMMY_HPP

#include <iostream>
#include <string>
#include "ATarget.hpp"

using namespace std;

class Dummy : public ATarget {
    
    public:
        Dummy() : ATarget("Target Practice Dummy") {}
        ~Dummy() {}
        virtual ATarget * clone () const {
            return new Dummy();
        }
};

#endif