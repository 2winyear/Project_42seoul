#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include <string>
#include <iostream>
#include <map>
#include "ASpell.hpp"
#include "ATarget.hpp"

using namespace std;

class Warlock {
    private:
        string name;
        string title;

        Warlock() {}
        Warlock& operator=(const Warlock&);
        Warlock(const Warlock&) {}

        map <string, ASpell*> book;

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
            book.insert(make_pair(spell->getName(), spell->clone()));
        }
        void forgetSpell(const string& name) {
            if (book.find(name) == book.end())
                return ;
            book.erase(name);
        }
        void launchSpell(const string& name, ATarget& target) {
            if (book.find(name) == book.end())
                return ;
            ASpell* spell = book.at(name);
            spell->launch(target);
        }
};

#endif