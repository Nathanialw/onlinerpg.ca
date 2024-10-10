'use strict'

var swoosh;
var title;
var forest;
var cave;

function CreateSound(path) {
    var sound = new Howl ({
        src: [path],
        html5: true
    });
    return sound;
}

export function Init () {
    console.log("sound init");
    swoosh = CreateSound('../../assets/sounds/swish_2.wav');
    cave = CreateSound('../..//assets/music/forest/Dungeon_-_Catacomb_Crawler.ogg');
    forest = CreateSound('../../assets/music/forest/Dungeon_-_Thorn_Maze.ogg');
}

export function Init_Title() {
    title = CreateSound('../../assets/music/title/Title_Screen.ogg');
}

export function SoundPlay(keyName) {
    console.log("SoundPlay");
    swoosh.play();
    return true
}

export function Music_Play(zone) {
    if (zone === "forest") {
        forest.loop(true);
        forest.play();
    }
    else if (zone === "cave") {
        cave.loop(true);
        cave.play();
    }
    else if (zone === "title") {
        title.loop(true);
        title.play();
    }
    else {
        console.log("Invalid zone");
    }
}

export function SoundAttack() {
    console.log("Attack sound play!");
    swoosh.play();
}

