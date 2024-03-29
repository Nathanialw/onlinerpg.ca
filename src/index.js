const app = new PIXI.Application();
await app.init({ width: 480, height: 480 })
document.body.appendChild(app.canvas);

let mapDisplay = [];
let player;
let enemies = []
let objects = []

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

let fill = [];

function MakeMap(mapString, mapWidth) {
    console.log(mapString);
    for (let i = 0; i < mapWidth; i++) {
        //render lines of the map
        let object = mapString.substring((i * mapWidth), ((i * mapWidth) + mapWidth));
        mapDisplay[i] = new PIXI.Text(object, {fontFamily : "'Press Start 2P'", fontSize: 24, fill : 0xff1010, align : 'center'});
        mapDisplay[i].y = i * 24;  // Assuming each cell is 24 pixels tall
        app.stage.addChild(mapDisplay[i]);

        // sent floor under units
        for (let j = 0; j < mapWidth; j++) {
            let object = mapString.substring([(i * mapWidth)], (i * mapWidth) + mapWidth);

            if (object[j] === 'H') {
                fill.push(createTextWithBackground('.', {fontFamily : "'Press Start 2P'", fontSize: 24, fill : 0xff1010, align : 'center'}, 0x000001));
                fill[fill.length - 1].x = j * 24;  // Assuming each cell is 24 pixels tall
                fill[fill.length - 1].y = i * 24;  // Assuming each cell is 24 pixels tall
            }
                app.stage.addChild(fill[fill.length - 1]);
            else if (object[j] === 'g') {
                fill.push(createTextWithBackground('.', {fontFamily : "'Press Start 2P'", fontSize: 24, fill : 0xff1010, align : 'center'}, 0x000001));
                fill[fill.length - 1].x = j * 24;  // Assuming each cell is 24 pixels tall
                fill[fill.length - 1].y = i * 24;  // Assuming each cell is 24 pixels tall
                app.stage.addChild(fill[fill.length - 1]);
            }
            else if (object[j] === 'o') {
                fill.push(createTextWithBackground('.', {fontFamily : "'Press Start 2P'", fontSize: 24, fill : 0xff1010, align : 'center'}, 0x000001));
                fill[fill.length - 1].x = j * 24;  // Assuming each cell is 24 pixels tall
                fill[fill.length - 1].y = i * 24;  // Assuming each cell is 24 pixels tall
                app.stage.addChild(fill[fill.length - 1]);
            }
        }
    }

    // render units on the map
    for (let i = 0; i < mapWidth; i++) {
        for (let j = 0; j < mapWidth; j++) {
            let object = mapString.substring([(i * mapWidth)], (i * mapWidth) + mapWidth);

            if (object[j] === 'H') {
                player = createTextWithBackground('H', {fontFamily : "'Press Start 2P'", fontSize: 24, fill : 0xff1010, align : 'center'}, 0x000001);
                player.x = j * 24;
                player.y = i * 24;
                app.stage.addChild(player);
            }
            else if (object[j] === 'g') {
                enemies.push(createTextWithBackground('g', {fontFamily : "'Press Start 2P'", fontSize: 24, fill : 0xff1010, align : 'center'}, 0x000001));
                enemies[enemies.length - 1].x = j * 24
                enemies[enemies.length - 1].y = i * 24
                app.stage.addChild(enemies[enemies.length - 1]);
            }
            else if (object[j] === 'o') {
                objects.push(createTextWithBackground('o', {fontFamily : "'Press Start 2P'", fontSize: 24, fill : 0xff1010, align : 'center'}, 0x000001));
                objects[objects.length - 1].x = j * 24
                objects[objects.length - 1].y = i * 24
                app.stage.addChild(objects[objects.length - 1]);
            }
        }
    }
}



// Add a ticker callback to move the sprite back and forth
let elapsed = 0.0;

// app.ticker.add((ticker) => {
    //     // elapsed += ticker.deltaTime;
    //     // sprite.x = 100.0 + Math.cos(elapsed/50.0) * 100.0;D
    // });
    
export { player, MakeMap }