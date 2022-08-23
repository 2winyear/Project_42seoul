#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include <iostream>
#include <string>
#include <map>
#include "ASpell.hpp"
#include "ATarget.hpp"
#include "SpellBook.hpp"

using namespace std;

class Warlock {
    private:
        string _name;
        string _title;

        Warlock();
        Warlock(const Warlock &);
        Warlock& operator=(const Warlock &);

        SpellBook book;
    public:
        ~Warlock() {}
        Warlock(const string& name, const string& title) : _name(name), _title(title) {
            cout << getName() << ": This looks like another boring day.\n";
        }

        const string& getName () const {
            return this->_name;
        }
        const string& getTitle () const {
            return this->_title;
        }
        void setTitle (const string& title) {
            this->_title = title;
        }
        void introduce() const {
            cout << getName() << ": I am " << getName() << ", " << getTitle() << "!\n";
        }
        void learnSpell (ASpell * spell) {
            if (spell == NULL)
                return ;
            book.learnSpell(spell);
        }
        void forgetSpell (const string& name) {
            book.forgetSpell(name);
        }
        void launchSpell (const string& name, ATarget& target) {
            ASpell *spell = book.createSpell(name);
            if (spell != NULL)
                spell->launch(target);
        }
};

#endif