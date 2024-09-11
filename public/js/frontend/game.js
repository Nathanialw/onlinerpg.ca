export const app = new PIXI.Application();
await app.init({ width: 256, height: 256 })
document.getElementById('gameCanvas').appendChild(app.canvas);
