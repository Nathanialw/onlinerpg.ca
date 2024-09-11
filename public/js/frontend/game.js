import { swoosh, CreateSound } from "../sound/sound.js";
swoosh = CreateSound();

export const app = new PIXI.Application();
await app.init({ width: 288, height: 288 })
document.getElementById('gameCanvas').appendChild(app.canvas);
