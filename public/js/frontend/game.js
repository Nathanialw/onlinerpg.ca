import { Init } from "../sound/sound.js";
Init();

export const app = new PIXI.Application();
export let cellSize = 24;

export let viewportWidth = 41;
export let viewportHeight = 41;

let topPanelHeight = 40;
let topPanelWidth = viewportWidth;

let rightPanelWidth = 40;
let rightPanelHeight = viewportHeight + topPanelHeight;

let leftPanelWidth = 40;
let leftPanelHeight = viewportHeight + topPanelHeight;

let bottomPanelWidth = leftPanelWidth + rightPanelWidth + viewportWidth;
let bottomPanelHeight = 40;

let gameWindow = viewportWidth + 0;

function Set_Window_Width() {
    return (viewportWidth * cellSize) + (leftPanelWidth * cellSize) + (rightPanelWidth * cellSize);
}
function Set_Window_Height() {
    return (viewportHeight * cellSize) + (topPanelHeight * cellSize) + (bottomPanelHeight * cellSize);
}

async function Start_Game() {//13
    await app.init({ width: Set_Window_Width(), height: Set_Window_Height() })
    document.getElementById('gameCanvas').appendChild(app.canvas);
    Draw_Title_Screen()
}

function Draw_Game_Window() {
    let gameWindow = new PIXI.Graphics();
    gameWindow.beginFill(0x020000);
    gameWindow.drawRect(0, 0, Set_Window_Width(), Set_Window_Height());
    gameWindow.endFill();
    app.stage.addChild(gameWindow);
}

function Draw_Top_Panel() {
    let topPanel = new PIXI.Graphics();
    topPanel.beginFill(0x000300);
    topPanel.drawRect(0, 0, Set_Window_Width(), topPanelHeight * cellSize);
    topPanel.endFill();
    app.stage.addChild(topPanel);
}

function Draw_Right_Panel() {
    let rightPanel = new PIXI.Graphics();
    rightPanel.beginFill(0x000300);
    rightPanel.drawRect((viewportWidth + leftPanelWidth) * cellSize, 0, rightPanelWidth * cellSize, rightPanelHeight * cellSize);
    rightPanel.endFill();
    app.stage.addChild(rightPanel);
}

function Draw_Left_Panel() {
    let leftPanel = new PIXI.Graphics();
    leftPanel.beginFill(0x400000);
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
    map.beginFill(0x000006);
    map.drawRect(leftPanelWidth * cellSize, topPanelHeight * cellSize, viewportWidth * cellSize, viewportHeight * cellSize);
    map.endFill();
    app.stage.addChild(map);
}

function Draw_Map_Border() {
    let mapBorder = new PIXI.Graphics();
    mapBorder.lineStyle(1, 0xffffff, 1);
    mapBorder.drawRect(leftPanelWidth * cellSize, topPanelHeight * cellSize, viewportWidth * cellSize, viewportHeight * cellSize);
    app.stage.addChild(mapBorder);
}

function Draw_Player_Stats() {
    let playerStats = new PIXI.Graphics();
    playerStats.beginFill(0x300400);
    playerStats.drawRect(0, topPanelHeight * cellSize, leftPanelWidth * cellSize, viewportHeight * cellSize);
    playerStats.endFill();
    app.stage.addChild(playerStats);
}

function Draw_Player_Stats_Border() {
    let playerStatsBorder = new PIXI.Graphics();
    playerStatsBorder.lineStyle(1, 0xffffff, 1);
    playerStatsBorder.drawRect(0, topPanelHeight * cellSize, leftPanelWidth * cellSize, viewportHeight * cellSize);
    app.stage.addChild(playerStatsBorder);
}


function Draw_Title_Screen() {
    let title = new PIXI.Text("Online RPG", {fontFamily : "'Press Start 2P'", fontSize: 24, fill : 0xff1010, align : 'center'});
    title.x = Set_Map_Within_Viewport(11) * cellSize;  // Assuming each cell is 24 pixels tall
    title.y = 200;  // Assuming each cell is 24 pixels tall
    app.stage.addChild(title);
    let subtitle = new PIXI.Text("Press enter to start!", {fontFamily : "'Press Start 2P'", fontSize: 16, fill : 0xff1010, align : 'center'});
    subtitle.x = Set_Map_Within_Viewport(13) * 24;  // Assuming each cell is 24 pixels tall
    subtitle.y = 300;  // Assuming each cell is 24 pixels tall
    app.stage.addChild(subtitle);
}

function Splash_Screen() {
    //start game
    Start_Game();
}
Splash_Screen()

export function Close_Game() {
    document.getElementById('gameCanvas').removeChild(app.canvas);    
    app.destroy(true, {children: true, texture: true, baseTexture: true});
        // Create a form element
        const form = document.createElement('form');
        form.method = 'post';
    
        // Create an input element
        const input = document.createElement('input');
        input.type = 'submit';
        input.name = 'restartGame';
        input.id = 'restartGame';
        input.className = 'wrapper btn btn-submit';
        input.value = 'Restart Game';
    
        // Append the input to the form
        form.appendChild(input);
    
        // Append the form to the gameCanvas
        document.getElementById('gameCanvas').appendChild(form);
    
}

export function Set_Map_Within_Viewport(visionWidth) {
    let vision = ((viewportWidth - 1) / 2) - ((visionWidth - 1) / 2);
    return vision;
}

export function Set_Player_Withing_Viewport() {
    
    return ((viewportWidth - 1) / 2);
}