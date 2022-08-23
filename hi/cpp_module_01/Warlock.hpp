#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include <iostream>
#include <string>
#include <map>
#include "ASpell.hpp"
#include "ATarget.hpp"

using namespace std;

class Warlock {
    private:
        string _name;
        string _title;

        Warlock();
        Warlock(const Warlock &);
        Warlock& operator=(const Warlock &);

        map<string, ASpell *> book;
    public:
        ~Warlock() {
            cout << getName() << ": My job here is done!\n";

            map<string, ASpell *> ::iterator it;
            for (it = book.begin(); it != book.end(); it++) {
                delete it->second;
            }

        }
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
            book.insert(make_pair(spell->getName(), spell->clone()));
        }
        void forgetSpell (const string& name) {
            if (book.find(name) == book.end())
                return ;
            delete book[name];
            book.erase(name);
        }
        void launchSpell (const string& name, ATarget& target) {
            if (book.find(name) == book.end())
                return ;
            ASpell *spell = book.at(name);
            spell->launch(target);
        }
};

#endif