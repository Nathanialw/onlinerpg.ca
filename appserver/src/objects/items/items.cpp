//
// Created by desktop on 10/12/24.
//

#include "items.h"

namespace  Items {

     ItemEffectUID Get_Item_Effect(ItemID itemID) {
	     return itemEffects[itemID];
     }
}