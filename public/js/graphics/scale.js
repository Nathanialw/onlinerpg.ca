'use strict'

import { Set_Font_Size } from './graphics.js';
import { Update_Screen } from '../frontend/ui.js';

// List of media queries with their respective min-width values
const mediaQueries = [
    { query: window.matchMedia('(min-width: 1px)'), width: 1 },
    { query: window.matchMedia('(min-width: 1280px)'), width: 1280 },
    { query: window.matchMedia('(min-width: 1920px)'), width: 1920 },
    { query: window.matchMedia('(min-width: 2560px)'), width: 2560 },
    { query: window.matchMedia('(min-width: 3840px)'), width: 3840 }
];

function Update8() {
    Set_Font_Size(8);
    Update_Screen()
}
function Update12() {
    Set_Font_Size(12);
    Update_Screen()
}
function Update16() {
    Set_Font_Size(16);
    Update_Screen()
}
function Update24() {
    Set_Font_Size(24);
    Update_Screen()
}

let Update = {
    1280: Update8,
    1920: Update12,
    2560: Update16,
    3840: Update24,
}

function handleMediaQueryChange() {

    // Loop through the media queries and log the matched width
    mediaQueries.forEach(({ query, width }) => {
        if (query.matches) {
            console.log(`Media Query Matched! Width: ${width}px`);
        }
        if (query.matches && width === 1) {
            Set_Font_Size(8);        
        }
        if (query.matches && width === 1280) {
            Set_Font_Size(12);
            Update_Screen()
            return;
        }
        else if (query.matches && width === 1920) {
            Set_Font_Size(16);
            Update_Screen()
            return;
        }
        else if (query.matches && width === 2560) {
            Set_Font_Size(24);
            Update_Screen()
            return;
        }
        else if (query.matches && width === 3840) {
            Set_Font_Size(24);
            Update_Screen()
            return;
        }        
    });
}

// Register event listeners and perform initial check
mediaQueries.forEach(({ query }) => {
    query.addEventListener('change', handleMediaQueryChange);
});

// handleMediaQueryChange(); // Initial check
