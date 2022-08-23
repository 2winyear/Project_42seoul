#ifndef TARGETGENERATOR_HPP
#define TARGETGENERATOR_HPP

#include <iostream>
#include <string>
#include <map>
#include "ASpell.hpp"
#include "ATarget.hpp"
#include "SpellBook.hpp"

using namespace std;

class TargetGenerator {
    private:
        string _name;
        string _title;

        TargetGenerator(const TargetGenerator &) {}
        TargetGenerator& operator=(const TargetGenerator &);

        map<string, ATarget*> book;
    public:
        TargetGenerator() {}
        ~TargetGenerator() {
            map<string, ATarget *> ::iterator it;

            for (it = book.begin(); it != book.end(); it++) {
                delete it->second;
            }
        }
        void learnTargetType(ATarget* target) {
            if (target == NULL)
                return ;
            book.insert(make_pair(target->getType(), target->clone()));
        }
        void forgetTargetType(string const & type) {
            if (book.find(type) == book.end())
                return ;
            delete book[type];
            book.erase(type);
        }
        ATarget* createTarget(string const & type) {
            if (book.find(type) == book.end())
                return NULL;
            return book.at(type);
        }
};

#endif