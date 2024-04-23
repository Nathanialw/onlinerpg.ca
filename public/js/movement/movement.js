import {socket} from "../networking/receive.js"
import {Move_Player} from "../objects/objects.js"
const cell_size = 24;

//up movement locally
//send movement to server
//recieve position from server
//replace local with server position of they aren't the same

function Move(keyName) {
    if (keyName === "w") {
        Move_Player(0, -cell_size);
        socket().send("1w");       
        //send to server
        return true;
    }
    
    else if (keyName === "a") {
        Move_Player(-cell_size, 0);
        socket().send("1a");       
        //send to server
        return true;
    }
    
    else if (keyName === "s") {
        Move_Player(0, cell_size)
        socket().send("1s");       
        //send to server
        return true;
    }
    
    else if (keyName === "d") {
        Move_Player(cell_size, 0);
        socket().send("1d");       
        //send to server
        return true;
    }
    return false;
}

export {Move}
