import {socket} from "../networking/socket.js"


//send data to server
function Send() {
    let conn = socket()
    
    //get data from form
    let name = document.getElementById("name").value;
    
    let gender = document.getElementById("gender").value;
    let race = document.getElementById("race").value;
    let unitClass = document.getElementById("class").value;
    let alignment = document.getElementById("alignment").value;

    if (conn.isConnected) {
        conn.websocket.send("2" + name + gender + race + unitClass + alignment);       
        console.log("char create Data sent to server")
    }
    else {
        console.log("Error: Server is not connected")
    }
}

document.getElementById('startGame').addEventListener('change', (event) => {
    Send();
});