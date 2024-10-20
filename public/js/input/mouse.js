'use strict'

function Interrogate_Cell() {

    // it should return the uID of the unit in the cell
    let cell = Get_Cell_At_Mouse_Position();
    if (cell) {
        app.stage.addEventListner("click", () => {
            console.log(cell);
        });
    }
}


export function Set_Cursor_Hover(target, target) {
    target.eventMode = 'static';
    if (target === 'enemy') {
        target.cursor = 'crosshair';
    }
    else if (target === 'ally') {
        target.cursor = 'hover';
    }
    else if (target === 'neutral') {
        target.cursor = 'hover';
    }
    else {
        console.log("invalid target text");
    }
}
