#ifndef BRICKWALL_HPP
#define BRICKWALL_HPP

#include <iostream>
#include <string>
#include "ATarget.hpp"

using namespace std;

class BrickWall : public ATarget {
    
    public:
        BrickWall() : ATarget("Inconspicuous Red-brick Wall") {}
        ~BrickWall() {}
        virtual ATarget * clone () const {
            return new BrickWall();
        }
};

#endif