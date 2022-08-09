#include "ASpell.hpp"

ASpell::ASpell() {}

ASpell::ASpell(ASpell &temp) { *this = temp; }

ASpell::ASpell(const string &name, const string &effects) : _name(name), _effects(effects) {}

ASpell &ASpell::operator=(ASpell &temp) {
    this->_name = temp.getName();
    this->_effects = temp.getName();
    return *this;
}

ASpell::~ASpell() {}

const string &ASpell::getName() const {
    return this->_name;
}

const string &ASpell::getEffect() const {
    return this->_effects;
}