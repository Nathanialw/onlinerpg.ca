'use strict'
import {Target_Stats} from "./targetStats.js"
import {Spell_Book} from "./spellBook.js"
import {Combat_Log} from "./combatLog.js"
import {Minimap} from "./minimap.js"
import {Crafting} from "./crafting.js"
import {Loot} from "./loot.js"
import {Quests} from "./quests.js"

const GamePanels = [
    Target_Stats,
    Spell_Book,
    Crafting,
    Loot,  // sp it is out of the way unless needed
    Combat_Log,
    
    //not added yet
    Minimap,
    Quests, //starting panel that explains the game
]

export function Render_Game_Panel(gamePanelIndex) {
    GamePanels[gamePanelIndex]();
}