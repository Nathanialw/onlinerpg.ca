import { Init } from "../sound/sound.js";
Init();

export const app = new PIXI.Application();
await app.init({ width: 288, height: 288 })
document.getElementById('gameCanvas').appendChild(app.canvas);

export function closeGame() {
    app.destroy(true, {children: true, texture: true, baseTexture: true});
    document.getElementById('gameCanvas').removeChild(app.canvas);    
    document.getElementById('gameCanvas').innerHTML(`<form method='post'>
                <input type='submit' name='restartGame' id='restartGame' class='wrapper btn btn-submit' value='Restart Game'/>
            </form>`);
    
}