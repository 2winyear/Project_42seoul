#include "ATarget.hpp"

void ATarget::getHitBySpell(const ASpell& spell) const {
    cout << getType() << " has been " << spell.getEffects() << "!\n";
}