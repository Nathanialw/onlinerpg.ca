'use strict'
import {Target_Stats} from "./targetStats.js"
import {Spell_Book} from "./spellBook.js"
import {Combat_Log} from "./combatLog.js"
import {Minimap} from "./minimap.js"
import {Crafting} from "./crafting.js"

const GamePanels = [
    Target_Stats,
    Spell_Book,
    Combat_Log,
    Minimap,
    Crafting,
]

export function Render_Game_Panel(gamePanelIndex) {
    GamePanels[gamePanelIndex]();
}