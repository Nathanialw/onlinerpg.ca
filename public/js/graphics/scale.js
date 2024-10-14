'use strict'

import { Set_Font_Size } from './graphics.js';
import { Update_Screen, Update_Screen_Phone } from '../frontend/ui.js';

const mediaQueries = [
    { query: window.matchMedia('(min-width: 1px) and (max-width: 390px)'), size: 8 },
    { query: window.matchMedia('(min-width: 391px) and (max-width: 711px)'), size: 8 },
    { query: window.matchMedia('(min-width: 712px) and (max-width: 1279px)'), size: 8 },
    { query: window.matchMedia('(min-width: 1280px) and (max-width: 1919px)'), size: 12 },
    { query: window.matchMedia('(min-width: 1920px) and (max-width: 2559px)'), size: 16 },
    // { query: window.matchMedia('(min-width: 2560px) and (max-width: 3839px)'), size: 24 },
    { query: window.matchMedia('(min-width: 2560px) and (max-width: 3239px)'), size: 24 },
    { query: window.matchMedia('(min-width: 3240px) and (max-width: 3839px)'), size: 28 },
    { query: window.matchMedia('(min-width: 3840px)'), size: 32 }
];

function handleMediaQueryChange() {
    // Loop through the media queries in descending order and log the matched size
    for (let { query, size } of mediaQueries) {
        if (query.matches) {
            Set_Font_Size(size);
            Update_Screen()
            break; // Exit the loop after the first match
        }
    }
}

export function Set_Scale_Queries() {
    // Register event listeners and perform initial check
    // handleMediaQueryChange(); // Initial check

    // mediaQueries.forEach(({ query }) => {
    //     query.addEventListener('change', handleMediaQueryChange);
    // });
}
