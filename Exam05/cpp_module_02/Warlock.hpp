#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include <string>
#include <iostream>
#include <map>
#include "ASpell.hpp"
#include "ATarget.hpp"
#include "SpellBook.hpp"

using namespace std;

class Warlock {
    private:
        string name;
        string title;

        Warlock() {}
        Warlock& operator=(const Warlock&);
        Warlock(const Warlock&) {}

        SpellBook book;

    public:
        Warlock(const string& name, const string& title): name(name), title(title) {
            cout << getName() << ": This looks like another boring day.\n";
        }
        ~Warlock() {
            cout << getName() << ": My job here is done!\n";
        }
        const string& getName() const {
            return this->name;
        }
        const string& getTitle() const {
            return this->title;
        }
        void setTitle(const string& title) {
            this->title = title;
        }
        void introduce() const {
            cout << getName() << ": I am " << getName() << ", " << getTitle() << "!\n";
        }
        void learnSpell(ASpell* spell) {
            book.learnSpell(spell);
        }
        void forgetSpell(const string& name) {
            book.forgetSpell(name);
        }
        void launchSpell(const string& name, ATarget& target) {
            ASpell* spell = book.createSpell(name);
            if (spell == NULL)
                return ;    
            spell->launch(target);
        }
};

#endif