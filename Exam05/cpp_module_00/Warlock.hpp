#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include <iostream>
#include <string>

class Warlock {
    private:
        std::string name;
        std::string title;

        Warlock();
        Warlock(const Warlock &);
        Warlock &operator=(const Warlock &);

    public:
        const std::string &getName() const; //* getName, returns a reference to constant string
        const std::string &getTitle() const; //* getTitle, returns a reference to constant string
        //Both these functions will have to be callable on a constant Warlock.
        
        void setTitle(const std::string &);//* setTitle, returns void and takes a reference to constant string

        void introduce() const;
        // Your Warlock will also have, in addition to whatever's required by Coplien's
        // form, a constructor that takes, in this order, its name and title. Your Warlock
        // will not be able to be copied, instantiated by copy, or instantiated without a
        // name and a title.
        ~Warlock();
        Warlock(std::string, std::string);
};

#endif