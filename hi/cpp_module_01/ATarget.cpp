#include "ATarget.hpp"

ATarget::ATarget() {}

ATarget::ATarget(const ATarget &) {}

ATarget::ATarget(const string& type) : type(type) {}

const string& ATarget::getType () const {
    return this->type;
}

void ATarget::getHitBySpell(const ASpell& spell) const {
    cout << getType() << " has been " << spell.getEffects() << "!\n";
}