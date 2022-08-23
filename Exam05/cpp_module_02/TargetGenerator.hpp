#ifndef TARGETGENERATOR_HPP
#define TARGETGENERATOR_HPP

#include <string>
#include <iostream>
#include <map>
#include "ATarget.hpp"

using namespace std;

class TargetGenerator {
        TargetGenerator& operator=(const TargetGenerator&);
        TargetGenerator(const TargetGenerator&) {}

        map<string, ATarget*> book;

    public:
        TargetGenerator() {}
        ~TargetGenerator() {}
        void learnTargetType(ATarget* target) {
            book.insert(make_pair(target->getType(), target->clone()));
        }
        void forgetTargetType(string const & name) {
            if (book.find(name) == book.end())
                return ;
            book.erase(name);
        }
        ATarget* createTarget(string const & name) {
            if (book.find(name) == book.end())
                return NULL;
            return book.at(name);
        }
};

#endif