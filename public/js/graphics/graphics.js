'use strict'

export const app = new PIXI.Application();
export let cellSize = 24;

let footerHeight = 125;
let gameWindowOrigin_x = 0;
let gameWindowOrigin_y = 56; //3.5rem as per navbar height

export let viewportWidth = 41;
export let viewportHeight = 41;

let topPanelHeight = 10;
let topPanelWidth = viewportWidth;

let rightPanelWidth = 40;
let rightPanelHeight = viewportHeight + topPanelHeight;

let leftPanelWidth = 40;
let leftPanelHeight = viewportHeight + topPanelHeight;

let bottomPanelWidth = leftPanelWidth + rightPanelWidth + viewportWidth;
let bottomPanelHeight = (window.innerHeight / cellSize) - (viewportHeight + topPanelHeight);

let gameWindow = viewportWidth + 0;

function Set_Window_Width() {
    return (viewportWidth * cellSize) + (leftPanelWidth * cellSize) + (rightPanelWidth * cellSize);
}
function Set_Window_Height() {
    return (viewportHeight * cellSize) + (topPanelHeight * cellSize) + (bottomPanelHeight * cellSize);
}

function Get_ViewPort_Origin_x() {
    return leftPanelWidth;
}

function Get_ViewPort_Origin_y() {
    return topPanelHeight;
}


// function Draw_Game_Window() {
//     let gameWindow = new PIXI.Graphics();
//     gameWindow.beginFill(0x024030);
//     gameWindow.drawRect(0, gameWindowOrigin_y, Set_Window_Width(), Set_Window_Height());
//     gameWindow.endFill();
//     app.stage.addChild(gameWindow);
// }

function Draw_Top_Panel() {
    let topPanel = new PIXI.Graphics();
    topPanel.beginFill(0x0f0f0f);
    topPanel.drawRect(leftPanelWidth * cellSize, 0, topPanelWidth * cellSize, topPanelHeight * cellSize);
    topPanel.endFill();
    app.stage.addChild(topPanel);
}

function Draw_Right_Panel() {
    let rightPanel = new PIXI.Graphics();
    rightPanel.beginFill(0x300301);
    rightPanel.drawRect((viewportWidth + leftPanelWidth) * cellSize, 0, rightPanelWidth * cellSize, rightPanelHeight * cellSize);
    rightPanel.endFill();
    app.stage.addChild(rightPanel);
}

function Draw_Left_Panel() {
    let leftPanel = new PIXI.Graphics();
    leftPanel.beginFill(0x100030);
    leftPanel.drawRect(0, 0, leftPanelWidth * cellSize, leftPanelHeight * cellSize);
    leftPanel.endFill();
    app.stage.addChild(leftPanel);
}

function Draw_Bottom_Panel() {
    let bottomPanel = new PIXI.Graphics();
    bottomPanel.beginFill(0x000050);
    bottomPanel.drawRect(0, (viewportHeight + topPanelHeight) * cellSize, bottomPanelWidth * cellSize, bottomPanelHeight * cellSize);
    bottomPanel.endFill();
    app.stage.addChild(bottomPanel);
}

function Draw_Map() {
    let map = new PIXI.Graphics();
    map.beginFill(0x009900);
    map.drawRect(leftPanelWidth * cellSize, (topPanelHeight * cellSize), viewportWidth * cellSize, viewportHeight * cellSize);
    map.endFill();
    app.stage.addChild(map);
}

// function Draw_Map_Border() {
//     let mapBorder = new PIXI.Graphics();
//     mapBorder.lineStyle(1, 0xffffff, 1);
//     mapBorder.drawRect(leftPanelWidth * cellSize, topPanelHeight * cellSize, viewportWidth * cellSize, viewportHeight * cellSize);
//     app.stage.addChild(mapBorder);
// }

// function Draw_Player_Stats() {
//     let playerStats = new PIXI.Graphics();
//     playerStats.beginFill(0x300400);
//     playerStats.drawRect(0, topPanelHeight * cellSize, leftPanelWidth * cellSize, viewportHeight * cellSize);
//     playerStats.endFill();
//     app.stage.addChild(playerStats);
// }

// function Draw_Player_Stats_Border() {
//     let playerStatsBorder = new PIXI.Graphics();
//     playerStatsBorder.lineStyle(1, 0xffffff, 1);
//     playerStatsBorder.drawRect(0, topPanelHeight * cellSize, leftPanelWidth * cellSize, viewportHeight * cellSize);
//     app.stage.addChild(playerStatsBorder);
// }


export function Draw_Title_Screen() {
    let title = new PIXI.Text("Online RPG", {fontFamily : "'Press Start 2P'", fontSize: 24, fill : 0xff1010, align : 'center'});
    title.x = Get_ViewPort_Origin_x() + Set_Map_Within_Viewport(11) * cellSize;  // Assuming each cell is 24 pixels tall
    title.y = Get_ViewPort_Origin_y() + 200;  // Assuming each cell is 24 pixels tall
    app.stage.addChild(title);
    let subtitle = new PIXI.Text("Press enter to start!", {fontFamily : "'Press Start 2P'", fontSize: 16, fill : 0xff1010, align : 'center'});
    subtitle.x = Get_ViewPort_Origin_x() + Set_Map_Within_Viewport(13) * 24;  // Assuming each cell is 24 pixels tall
    subtitle.y = Get_ViewPort_Origin_y() + 300;  // Assuming each cell is 24 pixels tall
    app.stage.addChild(subtitle);
}

export async function Create_Canvas() {
    await app.init({ width: Set_Window_Width(), height: Set_Window_Height() - (gameWindowOrigin_y + footerHeight) })
    app.canvas.x = 0;
    app.canvas.y = 0;
    document.getElementById('gameCanvas').appendChild(app.canvas);
}

function createTextWithBackground(textString, style, backgroundColor) {
    // Create the text object
    let text = new PIXI.Text(textString, style);
    
    // Create a new Graphics object and draw a rectangle on it
    let background = new PIXI.Graphics();
    background.fill(backgroundColor);
    background.rect(0, 0, text.width, text.height);
    
    // Create a container and add the background and text to it
    let container = new PIXI.Container();
    container.addChild(background);
    container.addChild(text);
    
    return container;
}

export function Create_Object(char, x, y) {
    let object = createTextWithBackground(char, {fontFamily : "'Press Start 2P'", fontSize: 24, fill : 0xff1010, align : 'center'}, 0x000001);
    object.x = x * cellSize;  // Assuming each cell is 24 pixels tall
    object.y = y * cellSize;  // Assuming each cell is 24 pixels tall
    app.stage.addChild(object);
    return object;
}

export function Update_Text(container, newText) {
    let textObject = container.children[1]; // Access the text object
    textObject.text = newText;
    // Update the background size if necessary
    let background = container.children[0];
    background.clear();
    background.fill(0x000001);
    background.rect(0, 0, textObject.width, textObject.height);
}

export function Update(){    
    //clear canvas
    //redraw map
}

export function Create_Map_Line(char, indexHeight, visionWidth) {
    let object = new PIXI.Text(char, {fontFamily : "'Press Start 2P'", fontSize: 24, fill : 0xff1010, align : 'center'});
    object.x = (Get_ViewPort_Origin_x() + Set_Map_Within_Viewport(visionWidth)) * cellSize;  // Assuming each cell is 24 pixels tall
    object.y = (Get_ViewPort_Origin_y() + (Set_Map_Within_Viewport(visionWidth) + indexHeight)) * cellSize;  // Assuming each cell is 24 pixels tall
    app.stage.addChild(object);
    return object;
}


function Set_Map_Within_Viewport(visionWidth) {
    let vision = ((viewportWidth - 1) / 2) - ((visionWidth - 1) / 2);
    return vision;
}

function Set_Player_Within_Viewport() {
    return ((viewportWidth - 1) / 2);
}

export function Draw_UI() {
    Draw_Top_Panel();
    Draw_Right_Panel();
    Draw_Left_Panel();
    Draw_Bottom_Panel();
    Draw_Map();
    // Draw_Map_Border();
    // Draw_Player_Stats();
    // Draw_Player_Stats_Border();

}

// Add a ticker callback to move the sprite back and forth
let elapsed = 0.0;

// app.ticker.add((ticker) => {
    //     // elapsed += ticker.deltaTime;
    //     // sprite.x = 100.0 + Math.cos(elapsed/50.0) * 100.0;D
    // });
    
