'use strict'

import { Set_Font_Size } from './graphics.js';
import { Update_Screen, Update_Screen_Phone } from '../frontend/ui.js';

// List of media queries with their respective min-width values
const mediaQueries = [
    { query: window.matchMedia('(min-width: 1px)'), width: 1 },
    { query: window.matchMedia('(min-width: 1280px)'), width: 1280 },
    { query: window.matchMedia('(min-width: 1920px)'), width: 1920 },
    { query: window.matchMedia('(min-width: 2560px)'), width: 2560 },
    { query: window.matchMedia('(min-width: 3840px)'), width: 3840 }
];

function handleMediaQueryChange() {

    // Loop through the media queries and log the matched width
    mediaQueries.forEach(({ query, width }) => {
        if (query.matches) {
            console.log("width: ", window.width);
            console.log(`Media Query Matched! Width: ${width}px`);
        }
        if (query.matches && width === 1) {
            Set_Font_Size(8);        
            Update_Screen_Phone();
        }
        if (query.matches && width === 391) { //phone   
            Set_Font_Size(8);
            Update_Screen_Phone()
        }
        if (query.matches && width === 712) { //tablet
            Set_Font_Size(8);
            Update_Screen_Phone()
        }
        if (query.matches && width === 1280) {
            Set_Font_Size(12);
            Update_Screen()
        }
        if (query.matches && width === 1920) {
            Set_Font_Size(16);
            Update_Screen()
        }
        if (query.matches && width === 2560) {
            Set_Font_Size(24);
            Update_Screen()
        }
        if (query.matches && width === 3840) {
            Set_Font_Size(24);
            Update_Screen()
        }        
    });
}

// Register event listeners and perform initial check
mediaQueries.forEach(({ query }) => {
    query.addEventListener('change', handleMediaQueryChange);
});

handleMediaQueryChange(); // Initial check
