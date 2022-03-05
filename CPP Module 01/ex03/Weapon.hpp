#ifndef WEAPON_HPP
# define WEAPON_HPP
# include <iostream>
# include <string>

class Weapon {
    private:
        std::string _type;
        Weapon(void);
    public:
        Weapon(std::string type);
        ~Weapon(void);
        std::string &getType(void);
        void setType(std::string type);
};

#endif