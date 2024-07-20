'use strict'

function Interrogate_Cell() {

    // it should return the uID of the unit in the cell
    let cell = Get_Cell_At_Mouse_Position();
    if (cell) {
        console.log(cell);
    }
}
