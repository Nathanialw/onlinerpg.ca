//
// Created by desktop on 10/30/24.
//
#include "use_effects.h"
#include "array"

namespace Use_Effects {

     std::array<std::function<void(Unit::Unit &unit, uint8_t value)>, 256> Item_Effect_Map;

     void Trigger_Effect(Unit::Unit &unit, ItemEffectUID effectUid, uint8_t value) {
	     Item_Effect_Map[effectUid](unit, value);
     }


     void NOTHING(Unit::Unit &unit, uint8_t value) {
	     std::cout << "The potion does Nothing." << std::endl;
     }

     void Heal(Unit::Unit &unit, uint8_t value) {
	     std::cout << "unit: " << unit.stats.health << " heal value: " << (int)value << std::endl;
	     if ((unit.stats.health + value) > unit.stats.healthMax) {
		     //increase max health on overheal
		     auto  overHeal = (unit.stats.health + value) - unit.stats.healthMax;
		     unit.stats.healthMax = unit.stats.healthMax + (overHeal/10);
		     unit.stats.health = unit.stats.healthMax;
	     } else {
		     unit.stats.health += value;
	     }
	     std::cout << "unit: " << unit.stats.health << std::endl;
     }


     //TODO: add item effects
     void Init() {
	     Item_Effect_Map[0] = NOTHING;
	     Item_Effect_Map[1] = Heal;
	     Item_Effect_Map[2] = Heal;
	     Item_Effect_Map[3] = Heal;
	     Item_Effect_Map[4] = Heal;
	     Item_Effect_Map[5] = Heal;
	     Item_Effect_Map[6] = Heal;
	     Item_Effect_Map[7] = Heal;
	     Item_Effect_Map[8] = Heal;
	     Item_Effect_Map[9] = Heal;
	     Item_Effect_Map[10] = Heal;
	     Item_Effect_Map[11] = Heal;
	     Item_Effect_Map[12] = Heal;
	     Item_Effect_Map[13] = Heal;
	     Item_Effect_Map[14] = Heal;
	     Item_Effect_Map[15] = Heal;
	     Item_Effect_Map[16] = Heal;
	     Item_Effect_Map[17] = Heal;
	     Item_Effect_Map[18] = Heal;
	     Item_Effect_Map[19] = Heal;
	     Item_Effect_Map[20] = Heal;
	     Item_Effect_Map[21] = Heal;
	     Item_Effect_Map[22] = Heal;
	     Item_Effect_Map[23] = Heal;
	     Item_Effect_Map[24] = Heal;
	     Item_Effect_Map[25] = Heal;
	     Item_Effect_Map[26] = Heal;
	     Item_Effect_Map[27] = Heal;
	     Item_Effect_Map[28] = Heal;
	     Item_Effect_Map[29] = Heal;
	     Item_Effect_Map[30] = Heal;
	     Item_Effect_Map[31] = Heal;
	     Item_Effect_Map[32] = Heal;
	     Item_Effect_Map[33] = Heal;
	     Item_Effect_Map[34] = Heal;
	     Item_Effect_Map[35] = Heal;
	     Item_Effect_Map[36] = Heal;
	     Item_Effect_Map[37] = Heal;
	     Item_Effect_Map[38] = Heal;
	     Item_Effect_Map[39] = Heal;
	     Item_Effect_Map[40] = Heal;
	     Item_Effect_Map[41] = Heal;
	     Item_Effect_Map[42] = Heal;
	     Item_Effect_Map[43] = Heal;
	     Item_Effect_Map[44] = Heal;
	     Item_Effect_Map[45] = Heal;
	     Item_Effect_Map[46] = Heal;
	     Item_Effect_Map[47] = Heal;
	     Item_Effect_Map[48] = Heal;
	     Item_Effect_Map[49] = Heal;
	     Item_Effect_Map[50] = Heal;
	     Item_Effect_Map[51] = Heal;
	     Item_Effect_Map[52] = Heal;
	     Item_Effect_Map[53] = Heal;
	     Item_Effect_Map[54] = Heal;
	     Item_Effect_Map[55] = Heal;
	     Item_Effect_Map[56] = Heal;
	     Item_Effect_Map[57] = Heal;
	     Item_Effect_Map[58] = Heal;
	     Item_Effect_Map[59] = Heal;
	     Item_Effect_Map[60] = Heal;
	     Item_Effect_Map[61] = Heal;
	     Item_Effect_Map[62] = Heal;
	     Item_Effect_Map[63] = Heal;
	     Item_Effect_Map[64] = Heal;
	     Item_Effect_Map[65] = Heal;
	     Item_Effect_Map[66] = Heal;
	     Item_Effect_Map[67] = Heal;
	     Item_Effect_Map[68] = Heal;
	     Item_Effect_Map[69] = Heal;
	     Item_Effect_Map[70] = Heal;
	     Item_Effect_Map[71] = Heal;
	     Item_Effect_Map[72] = Heal;
	     Item_Effect_Map[73] = Heal;
	     Item_Effect_Map[74] = Heal;
	     Item_Effect_Map[75] = Heal;
	     Item_Effect_Map[76] = Heal;
	     Item_Effect_Map[77] = Heal;
	     Item_Effect_Map[78] = Heal;
	     Item_Effect_Map[79] = Heal;
	     Item_Effect_Map[80] = Heal;
	     Item_Effect_Map[81] = Heal;
	     Item_Effect_Map[82] = Heal;
	     Item_Effect_Map[83] = Heal;
	     Item_Effect_Map[84] = Heal;
	     Item_Effect_Map[85] = Heal;
	     Item_Effect_Map[86] = Heal;
	     Item_Effect_Map[87] = Heal;
	     Item_Effect_Map[88] = Heal;
	     Item_Effect_Map[89] = Heal;
	     Item_Effect_Map[90] = Heal;
	     Item_Effect_Map[91] = Heal;
	     Item_Effect_Map[92] = Heal;
	     Item_Effect_Map[93] = Heal;
	     Item_Effect_Map[94] = Heal;
	     Item_Effect_Map[95] = Heal;
	     Item_Effect_Map[96] = Heal;
	     Item_Effect_Map[97] = Heal;
	     Item_Effect_Map[98] = Heal;
	     Item_Effect_Map[99] = Heal;
	     Item_Effect_Map[100] = Heal;
	     Item_Effect_Map[101] = Heal;
	     Item_Effect_Map[102] = Heal;
	     Item_Effect_Map[103] = Heal;
	     Item_Effect_Map[104] = Heal;
	     Item_Effect_Map[105] = Heal;
	     Item_Effect_Map[106] = Heal;
	     Item_Effect_Map[107] = Heal;
	     Item_Effect_Map[108] = Heal;
	     Item_Effect_Map[109] = Heal;
	     Item_Effect_Map[110] = Heal;
	     Item_Effect_Map[111] = Heal;
	     Item_Effect_Map[112] = Heal;
	     Item_Effect_Map[113] = Heal;
	     Item_Effect_Map[114] = Heal;
	     Item_Effect_Map[115] = Heal;
	     Item_Effect_Map[116] = Heal;
	     Item_Effect_Map[117] = Heal;
	     Item_Effect_Map[118] = Heal;
	     Item_Effect_Map[119] = Heal;
	     Item_Effect_Map[120] = Heal;
	     Item_Effect_Map[121] = Heal;
	     Item_Effect_Map[122] = Heal;
	     Item_Effect_Map[123] = Heal;
	     Item_Effect_Map[124] = Heal;
	     Item_Effect_Map[125] = Heal;
	     Item_Effect_Map[126] = Heal;
	     Item_Effect_Map[127] = Heal;
	     Item_Effect_Map[128] = Heal;
	     Item_Effect_Map[129] = Heal;
	     Item_Effect_Map[130] = Heal;
	     Item_Effect_Map[131] = Heal;
	     Item_Effect_Map[132] = Heal;
	     Item_Effect_Map[133] = Heal;
	     Item_Effect_Map[134] = Heal;
	     Item_Effect_Map[135] = Heal;
	     Item_Effect_Map[136] = Heal;
	     Item_Effect_Map[137] = Heal;
	     Item_Effect_Map[138] = Heal;
	     Item_Effect_Map[139] = Heal;
	     Item_Effect_Map[140] = Heal;
	     Item_Effect_Map[141] = Heal;
	     Item_Effect_Map[142] = Heal;
	     Item_Effect_Map[143] = Heal;
	     Item_Effect_Map[144] = Heal;
	     Item_Effect_Map[145] = Heal;
	     Item_Effect_Map[146] = NOTHING;
	     Item_Effect_Map[147] = NOTHING;
	     Item_Effect_Map[148] = NOTHING;
	     Item_Effect_Map[149] = NOTHING;
	     Item_Effect_Map[150] = NOTHING;
	     Item_Effect_Map[151] = NOTHING;
	     Item_Effect_Map[152] = NOTHING;
	     Item_Effect_Map[153] = NOTHING;
	     Item_Effect_Map[154] = NOTHING;
	     Item_Effect_Map[155] = NOTHING;
	     Item_Effect_Map[156] = NOTHING;
	     Item_Effect_Map[157] = NOTHING;
	     Item_Effect_Map[158] = NOTHING;
	     Item_Effect_Map[159] = NOTHING;
	     Item_Effect_Map[160] = NOTHING;
	     Item_Effect_Map[161] = NOTHING;
	     Item_Effect_Map[162] = NOTHING;
	     Item_Effect_Map[163] = NOTHING;
	     Item_Effect_Map[164] = NOTHING;
	     Item_Effect_Map[165] = NOTHING;
	     Item_Effect_Map[166] = NOTHING;
	     Item_Effect_Map[167] = NOTHING;
	     Item_Effect_Map[168] = NOTHING;
	     Item_Effect_Map[169] = NOTHING;
	     Item_Effect_Map[170] = NOTHING;
	     Item_Effect_Map[171] = NOTHING;
	     Item_Effect_Map[172] = NOTHING;
	     Item_Effect_Map[173] = NOTHING;
	     Item_Effect_Map[174] = NOTHING;
	     Item_Effect_Map[175] = NOTHING;
	     Item_Effect_Map[176] = NOTHING;
	     Item_Effect_Map[177] = NOTHING;
	     Item_Effect_Map[178] = NOTHING;
	     Item_Effect_Map[179] = NOTHING;
	     Item_Effect_Map[180] = NOTHING;
	     Item_Effect_Map[181] = NOTHING;
	     Item_Effect_Map[182] = NOTHING;
	     Item_Effect_Map[183] = NOTHING;
	     Item_Effect_Map[184] = NOTHING;
	     Item_Effect_Map[185] = NOTHING;
	     Item_Effect_Map[186] = NOTHING;
	     Item_Effect_Map[187] = NOTHING;
	     Item_Effect_Map[188] = NOTHING;
	     Item_Effect_Map[189] = NOTHING;
	     Item_Effect_Map[190] = NOTHING;
	     Item_Effect_Map[191] = NOTHING;
	     Item_Effect_Map[192] = NOTHING;
	     Item_Effect_Map[193] = NOTHING;
	     Item_Effect_Map[194] = NOTHING;
	     Item_Effect_Map[195] = NOTHING;
	     Item_Effect_Map[196] = NOTHING;
	     Item_Effect_Map[197] = NOTHING;
	     Item_Effect_Map[198] = NOTHING;
	     Item_Effect_Map[199] = NOTHING;
	     Item_Effect_Map[200] = NOTHING;
	     Item_Effect_Map[201] = NOTHING;
	     Item_Effect_Map[202] = NOTHING;
	     Item_Effect_Map[203] = NOTHING;
	     Item_Effect_Map[204] = NOTHING;
	     Item_Effect_Map[205] = NOTHING;
	     Item_Effect_Map[206] = NOTHING;
	     Item_Effect_Map[207] = NOTHING;
	     Item_Effect_Map[208] = NOTHING;
	     Item_Effect_Map[209] = NOTHING;
	     Item_Effect_Map[210] = NOTHING;
	     Item_Effect_Map[211] = NOTHING;
	     Item_Effect_Map[212] = NOTHING;
	     Item_Effect_Map[213] = NOTHING;
	     Item_Effect_Map[214] = NOTHING;
	     Item_Effect_Map[215] = NOTHING;
	     Item_Effect_Map[216] = NOTHING;
	     Item_Effect_Map[217] = NOTHING;
	     Item_Effect_Map[218] = NOTHING;
	     Item_Effect_Map[219] = NOTHING;
	     Item_Effect_Map[220] = NOTHING;
	     Item_Effect_Map[221] = NOTHING;
	     Item_Effect_Map[222] = NOTHING;
	     Item_Effect_Map[223] = NOTHING;
	     Item_Effect_Map[224] = NOTHING;
	     Item_Effect_Map[225] = NOTHING;
	     Item_Effect_Map[226] = NOTHING;
	     Item_Effect_Map[227] = NOTHING;
	     Item_Effect_Map[228] = NOTHING;
	     Item_Effect_Map[229] = NOTHING;
	     Item_Effect_Map[230] = NOTHING;
	     Item_Effect_Map[231] = NOTHING;
	     Item_Effect_Map[232] = NOTHING;
	     Item_Effect_Map[233] = NOTHING;
	     Item_Effect_Map[234] = NOTHING;
	     Item_Effect_Map[235] = NOTHING;
	     Item_Effect_Map[236] = NOTHING;
	     Item_Effect_Map[237] = NOTHING;
	     Item_Effect_Map[238] = NOTHING;
	     Item_Effect_Map[239] = NOTHING;
	     Item_Effect_Map[240] = NOTHING;
	     Item_Effect_Map[241] = NOTHING;
	     Item_Effect_Map[242] = NOTHING;
	     Item_Effect_Map[243] = NOTHING;
	     Item_Effect_Map[244] = NOTHING;
	     Item_Effect_Map[245] = NOTHING;
	     Item_Effect_Map[246] = NOTHING;
	     Item_Effect_Map[247] = NOTHING;
	     Item_Effect_Map[248] = NOTHING;
	     Item_Effect_Map[249] = NOTHING;
	     Item_Effect_Map[250] = NOTHING;
	     Item_Effect_Map[251] = NOTHING;
	     Item_Effect_Map[252] = NOTHING;
	     Item_Effect_Map[253] = NOTHING;
	     Item_Effect_Map[254] = NOTHING;
	     Item_Effect_Map[255] = NOTHING;

     }
}