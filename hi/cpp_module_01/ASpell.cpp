#include "ASpell.hpp"

ASpell::ASpell() {}

ASpell::ASpell(const ASpell &) {}

ASpell::ASpell(const string& name, const string& effects) : name(name), effects(effects) {}

const string& ASpell::getName() const {
    return this->name;
}

const string& ASpell::getEffects() const {
    return this->effects;
}

void ASpell::launch(const ATarget& target) const {
    target.getHitBySpell(*this);
}