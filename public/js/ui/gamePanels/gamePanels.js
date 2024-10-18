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
    Minimap,
    Spell_Book,
    Crafting,
    Combat_Log,
    
    //not added yet
    Loot,  // sp it is out of the way unless needed
    Quests, //starting panel that explains the game
]

export function Render_Game_Panel(gamePanelIndex) {
    GamePanels[gamePanelIndex]();
}