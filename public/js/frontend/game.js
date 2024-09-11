import { Init } from "../sound/sound.js";
Init();

export const app = new PIXI.Application();
await app.init({ width: 288, height: 288 })
document.getElementById('gameCanvas').appendChild(app.canvas);
