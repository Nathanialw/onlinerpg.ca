import {socket} from "../networking/receive.js"


function Send() {
    let conn = socket()

    //get data from form
    let name = document.getElementById("name").value;

    let gender = document.getElementById("gender").value;
    let race = document.getElementById("race").value;
    let unitClass = document.getElementById("class").value;
    let alignment = document.getElementById("alignment").value;


    //send data to server
    document.getElementById('startGame').addEventListener('change', (event) => {
        if (conn.isConnected) {
            conn.websocket.send(name + gender + race + unitClass + alignment);       
        }
    });
}