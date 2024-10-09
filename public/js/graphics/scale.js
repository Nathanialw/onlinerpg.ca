'use strict'

import { cellSize, minimapCellSize, Make_Map, Draw_Map, Draw_UI } from './graphics.js';
import { characterInfo } from '../frontend/unitdef.js';
import { Render_Target_Stats } from '../frontend/stats.js';
import { visionWidth, direction, species, damage, isDead, serverMap, Render_Log, Display_Damage } from '../frontend/ui.js';

export function Update_Screen() {
    Draw_UI(characterInfo);
    Make_Map(serverMap, visionWidth);
    Draw_Map(visionWidth, direction);
    
    // Display_Damage_Taken(species, damageTaken);
    Display_Damage(species, damage, isDead)
    Render_Log();
    Render_Target_Stats();
}

// List of media queries with their respective min-width values
const mediaQueries = [
    { query: window.matchMedia('(max-width: 1280px)'), width: 1280 },
    { query: window.matchMedia('(max-width: 1920px)'), width: 1920 },
    { query: window.matchMedia('(max-width: 2560px)'), width: 2560 },
    { query: window.matchMedia('(max-width: 3840px)'), width: 3840 }
];

function handleMediaQueryChange() {
    // Loop through the media queries and log the matched width
    mediaQueries.forEach(({ query, width }) => {
        if (query.matches) {
            console.log(`Media Query Matched! Width: ${width}px`);
        }
        if (query.matches && width === 1280) {
            cellSize = 8;
            minimapCellSize = 4;
            Update_Screen()
        }
        if (query.matches && width === 1920) {
            cellSize = 12;
            minimapCellSize = 6;
            Update_Screen()
        }
        if (query.matches && width === 2560) {
            cellSize = 16;
            minimapCellSize = 8;
            Update_Screen()
        }
        if (query.matches && width === 3840) {
            cellSize = 24;
            minimapCellSize = 12;
            Update_Screen()
        }        
    });
}

// Register event listeners and perform initial check
mediaQueries.forEach(({ query }) => {
    query.addEventListener('change', handleMediaQueryChange);
});

handleMediaQueryChange(); // Initial check
