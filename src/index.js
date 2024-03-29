const app = new PIXI.Application();
await app.init({ width: 480, height: 480 })
document.body.appendChild(app.canvas);

// let mapString = ""; 
// for (let i = 0; i < 20; i++) {
//     for (let j = 0; j < 20; j++) {
//         mapString += map[i][j];
//     }
// }
;
let player;

function createTextWithBackground(textString, style, backgroundColor) {
    // Create the text object
    let text = new PIXI.Text(textString, style);

    // Create a new Graphics object and draw a rectangle on it
    let background = new PIXI.Graphics();
    background.beginFill(backgroundColor);
    background.drawRect(0, 0, text.width, text.height);
    background.endFill();

    // Create a container and add the background and text to it
    let container = new PIXI.Container();
    container.addChild(background);
    container.addChild(text);

    return container;
}
let mapDisplay = [];

function MakeMap(mapString, mapWidth) {
    console.log(mapString);
    for (let i = 0; i < 20; i++) {
        mapDisplay[i] = new PIXI.Text(mapString.substring((i * mapWidth), ((i * mapWidth) + mapWidth)), {fontFamily : "'Press Start 2P'", fontSize: 24, fill : 0xff1010, align : 'center'});
        mapDisplay[i].y = i * 24;  // Assuming each cell is 24 pixels tall
        app.stage.addChild(mapDisplay[i]);
    }
}

player = createTextWithBackground("H", {fontFamily : "'Press Start 2P'", fontSize: 24, fill : 0xff1010, align : 'center'}, 0x000001);
app.stage.addChild(player);
// Usage:

// Add a ticker callback to move the sprite back and forth
let elapsed = 0.0;

// app.ticker.add((ticker) => {
    //     // elapsed += ticker.deltaTime;
    //     // sprite.x = 100.0 + Math.cos(elapsed/50.0) * 100.0;D
    // });
    
export { player, MakeMap }