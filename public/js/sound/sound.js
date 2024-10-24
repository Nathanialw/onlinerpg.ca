'use strict'

var swoosh;
var title;
var forest;
var cave;
var playing;

function CreateSound(path) {
    var sound = new Howl ({
        src: [path],
        html5: true
    });
    return sound;
}

export function Init () {
    swoosh = CreateSound('../../assets/sounds/swish_2.wav');
    cave = CreateSound('../..//assets/music/cave/Dungeon_-_Catacomb_Crawler.ogg');
    forest = CreateSound('../../assets/music/forest/Dungeon_-_Thorn_Maze.ogg');
}

export function Init_Title() {
    title = CreateSound('../../assets/music/title/Battle_-_Temple_Tussle.ogg');
}

export function SoundPlay(keyName) {
    if (swoosh) {
        swoosh.play();
    }
    return true;
}

export function Music_Play(zone) {
    if (playing) {
        playing.stop();
    }

    if (zone === "forest") {
        playing = forest;
    } else if (zone === "cave") {
        playing = cave;
    } else if (zone === "title") {
        playing = title;
    }

    if (playing) {
        playing.loop(true);
        playing.play();
    }
}

export function SoundAttack() {
    if (swoosh) {
        swoosh.play();
    }
}

export function StopAllSounds() {
    if (swoosh) swoosh.stop();
    if (title) title.stop();
    if (forest) forest.stop();
    if (cave) cave.stop();
    if (playing) playing.stop();
}