export var socket =  new WebSocket("ws://www.saycum.com/ws");

let map = [[]];

socket.onmessage = function(event) {    
    if (event.data.emty())
        return

    // [0] type
    // if map [1][2] map size

    let type = event.data[0];
    let data = event.data.substring(1);
    
    if (type === "0") {
        //message
        console.log(data);
    }
    
    else if (type === "1") {
        
        let mapWidth = data.substring(0, 2)
        let serverMap = data.substring(2);
        // map data
        for (let i = 0; i < mapWidth; i++) {
            for (let j = 0; j < mapWidth; j++) {
                map[i][j] = serverMap[(i * mapWidth) + j];
                console.log(map[i][j]);
            }
        }
    }
};
