#include "ATarget.hpp"

const string &ATarget::getType() const {
    return this->_type;
}

void ATarget::getHitBySpell(const ASpell &spell) {
    cout << this->_type << " has been " << spell.getEffect() << "!\n";
}
