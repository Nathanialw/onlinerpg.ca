const app = new PIXI.Application();
await app.init({ width: 480, height: 480 })
document.body.appendChild(app.canvas);

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

export function Create_Object(char, x, y) {
    let object = createTextWithBackground(char, {fontFamily : "'Press Start 2P'", fontSize: 24, fill : 0xff1010, align : 'center'}, 0x000001);
    object.x = x * 24;  // Assuming each cell is 24 pixels tall
    object.y = y * 24;  // Assuming each cell is 24 pixels tall
    app.stage.addChild(object);
    return object;
}

export function Create_Map_Line(char, Indexheight) {
    let object = new PIXI.Text(char, {fontFamily : "'Press Start 2P'", fontSize: 24, fill : 0xff1010, align : 'center'});
    object.y = Indexheight * 24;  // Assuming each cell is 24 pixels tall
    app.stage.addChild(object);
    return object;
}


// Add a ticker callback to move the sprite back and forth
let elapsed = 0.0;

// app.ticker.add((ticker) => {
    //     // elapsed += ticker.deltaTime;
    //     // sprite.x = 100.0 + Math.cos(elapsed/50.0) * 100.0;D
    // });
    