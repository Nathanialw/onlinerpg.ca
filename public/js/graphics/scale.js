'use strict'

import { Set_Font_Size, Set_Cell_Size } from './graphics.js';
import { Update_Screen, Update_Screen_Phone } from '../frontend/ui.js';

const mediaQueries = [
    { query: window.matchMedia('(min-width: 1px) and (max-width: 390px)'), size: 10 }, //originally 8, added +2 to all of them to try to fit screen
    { query: window.matchMedia('(min-width: 391px) and (max-width: 711px)'), Size: 10 },
    { query: window.matchMedia('(min-width: 712px) and (max-width: 1279px)'), Size: 10 },
    { query: window.matchMedia('(min-width: 1280px) and (max-width: 1919px)'), Size: 10 },
    { query: window.matchMedia('(min-width: 1920px) and (max-width: 2559px)'), Size: 10 },
    // { query: window.matchMedia('(min-width: 2560px) and (max-width: 3839px)'), size: 24 },
    { query: window.matchMedia('(min-width: 2560px) and (max-width: 3239px)'), size: Set_Cell_Size(2560) },
    { query: window.matchMedia('(min-width: 3240px) and (max-width: 3839px)'), size: Set_Cell_Size(3240) },
    { query: window.matchMedia('(min-width: 3840px)'), size: Set_Cell_Size(3840) }
];



function handleMediaQueryChange() {
    // Loop through the media queries in descending order and log the matched size
    for (let { query, size } of mediaQueries) {
        console.log("cellsize: ", size)
        if (query.matches) {
            Set_Font_Size(size);
            Update_Screen()
            break; // Exit the loop after the first match
        }
    }
}

export function Set_Scale_Queries() {
    // Register event listeners and perform initial check
    handleMediaQueryChange(); // Initial check
    
    mediaQueries.forEach(({ query }) => {
        query.addEventListener('change', handleMediaQueryChange);
    });
}
