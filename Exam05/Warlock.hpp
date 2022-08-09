#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include <string>
#include <iostream>

class Warlock {
    private:
        std::string name;
        std::string title;

        Warlock();
        Warlock(Warlock &);
        Warlock &operator=(Warlock &);
        // Your Warlock will not be able to be copied, instantiated by copy, or instantiated without a
        // name and a title.
    
    public:
        ~Warlock() {
            std::cout << this->name << ": My job here is done!\n";
        }

        Warlock(std::string name, std::string title)
        : name(name), title(title) {
            std::cout << this->name << ": This looks like another boring day.\n";
        }

        const std::string &getName() const {
            return this->name;
        }

        const std::string &getTitle() const {
            return this->title;
        }

        void setTitle(const std::string &title) {
            this->title = title;
        }

        void introduce() const {
            std::cout << this->name << ": I am " << this->name << ", " << this->title << " !\n";
        }
};

#endif