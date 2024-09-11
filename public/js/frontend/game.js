export const app = new PIXI.Application();
await app.init({ width: 294, height: 294 })
document.getElementById('gameCanvas').appendChild(app.canvas);
