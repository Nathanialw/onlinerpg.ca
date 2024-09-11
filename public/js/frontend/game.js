export const app = new PIXI.Application();
await app.init({ width: 640, height: 640 })
document.getElementById('gameCanvas').appendChild(app.canvas);
