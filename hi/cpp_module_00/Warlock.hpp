#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include <iostream>
#include <string>

using namespace std;

class Warlock {
    private:
        string _name;
        string _title;

        Warlock();
        Warlock(Warlock &);
        Warlock &operator=(Warlock &);

    public:
        ~Warlock() {
            cout << getName() << ": My job here is done!\n";
        }
        Warlock(string name, string title) : _name(name), _title(title) {
            cout << getName() << ": This looks like another boring day.\n";
        }

        const string & getName () const {
            return this->_name;
        }
        const string & getTitle () const {
            return this->_title;
        }
        void setTitle (const string & title) {
            this->_title = title;
        }
        void introduce() const {
            cout << getName() << ": I am " << getName() << ", " << getTitle() << "!\n";
        }
};

#endif