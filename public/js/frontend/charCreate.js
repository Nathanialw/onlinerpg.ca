import { createWebSocket, socket, websocket } from '/js/networking/socket.js';

// document.addEventListener('DOMContentLoaded', () => {
//     createWebSocket();
// });


function connect_to_server() {
    createWebSocket();
    //wait for connection
    while (websocket.readyState === websocket.CONNECTING) {
        console.log("Connecting WebSocket...");
        //wait 1 sec
        setTimeout(() => {
            //check connection
            if (websocket.readyState === websocket.OPEN) {
                console.log("WebSocket connection opened");
                return
            }
        }, 1000);
    }
}

//send data to server
function Send() {
    connect_to_server();

    let conn = socket()
    
    //get data from form
    let name = document.getElementById("name").value;
    
    let gender = document.getElementById("gender").value;
    let race = document.getElementById("race").value;
    let unitClass = document.getElementById("class").value;
    let alignment = document.getElementById("alignment").value;

    if (conn.isConnected) {
        conn.websocket.send("3" + name + gender + race + unitClass + alignment);       
        console.log("char create Data sent to server")
    }
    else {
        console.log("Error: Server is not connected")
    }
}

document.getElementById('startGame').addEventListener('click', (event) => {
    Send();
    //remove form <section class='startButton'>
    const formSection = document.querySelector('.startButton');
    if (formSection) {
        formSection.remove();
    }

    // Function to dynamically load a script
    function loadScript(src, type = 'text/javascript') {
        const script = document.createElement('script');
        script.src = src;
        script.type = type;
        document.body.appendChild(script);
    }

    // Load required JavaScript files
    loadScript('/js/frontend/game.js', 'module');
    loadScript('/js/input/keyboard.js', 'module');
    loadScript('/js/networking/receive.js', 'module');
});