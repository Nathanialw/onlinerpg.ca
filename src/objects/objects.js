let player;
let enemies = []
let objects = []

export function Set_Player(object) {
    player = object;
}

export function Set_Enemies(object) {
    enemies = object;
}

export function Set_Objects(object) {
    objects = object;
}


export function Move_Player(x, y) {
    player.x += x;
    player.y += y;
}

export function Move_Enemies(object) {
    enemies.push(object);
}

export function Move_Objects(object) {
    objects.push(object);
}





// export {player, enemies, objects}