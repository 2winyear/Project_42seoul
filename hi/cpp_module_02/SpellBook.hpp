#ifndef SpellBook_HPP
#define SpellBook_HPP

#include <iostream>
#include <string>
#include <map>
#include "ATarget.hpp"

using namespace std;

class SpellBook {
        SpellBook(SpellBook &) {}
        SpellBook &operator=(SpellBook &);
        map<string, ASpell*> book;
    
    public:
        SpellBook() {}
        ~SpellBook() {
            map<string, ASpell *> ::iterator it;
            for (it = book.begin(); it != book.end(); it++) {
                delete it->second;
            }
        }
        void learnSpell(ASpell* spell) {
            if (spell == NULL)
                return ;
            book.insert(make_pair(spell->getName(), spell->clone()));
        }
        void forgetSpell(string const & name) {
            if (book.find(name) == book.end())
                return ;
            delete book[name];
            book.erase(name);
        }
        ASpell* createSpell(string const & name) {
            if (book.find(name) == book.end())
                return NULL;
            return book.at(name);
        }
};

#endif