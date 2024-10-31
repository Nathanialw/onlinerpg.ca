#pragma once
//
// Created by desktop on 10/30/24.
//

#include "units.h"

//TODO: 128 potion effects and 128 scroll effects

//TODO: 64 stat effects

// Heal
// Max Health
// Mana
// Max Mana

// Intellect
// Strength
// Speed

// Physical Resist
// Holy Resist
// Fire Resist
// Ice Resist
// Poison Resist
// Shadow Resist

// Haste
// Mana steal
//TODO: 64 special effects, if you drink a potion it has the effect on you, if you throw a potion it has the effect on the target

//POSITIVES on self
// Teleport
// Teleport Random Close
// Teleport Random World /// Rare, often an instant death
// Teleport to Nearest Town
// Invisibility
// Invulnerability
// Life Steal


//NEGATIVES on self
// Polymorph
// Shrink
// Silence
// Disorient

// Stun
// Fear

// Charm

// Sleep
// Slow
// Freeze
// Petrify

// Blind
// Confusion
// Poison
// Disease
// Curse
// Hex
// Root
// Disarm





namespace  Use_Effects {

     void Trigger_Effect(Unit::Unit &unit, ItemEffectUID effectUid, uint8_t value);
     void Init();

}
