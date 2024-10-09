'use strict'

import { cellSize, minimapCellSize } from './graphics.js';
import { Update_Screen } from '../frontend/ui.js';

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
