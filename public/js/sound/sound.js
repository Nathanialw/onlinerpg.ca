'use strict'

let Music = {
    title: null,
    forest: null,
    cave: null,
    playing: null
}

let Sounds = {
    swoosh: null
}

function CreateSound(path) {
    var sound = new Howl ({
        src: [path],
        html5: true
    });
    return sound;
}

function Load_Sound(sound, path) {
    if (sound == null) {
        sound = CreateSound(path);
    }
}

export function Init () {
    Load_Sound(Sounds.swoosh, '../../assets/sounds/swish_2.wav');
    Load_Sound(Music.cave, '../..//assets/music/cave/Dungeon_-_Catacomb_Crawler.ogg');
    Load_Sound(Music.forest, '../../assets/music/forest/Dungeon_-_Thorn_Maze.ogg');
}


//preload landing page sounds
export function Init_Title() {
    Load_Sound(Music.title, '../../assets/music/title/Battle_-_Temple_Tussle.ogg');
}

export function SoundPlay(keyName) {
    if (Sounds.swoosh) {
        Sounds.swoosh.play();
    }
    return true;
}

export function Music_Play(zone) {
    if (Music.playing) {
        Music.playing.stop();
    }

    if (zone === "forest") {
        Music.playing = forest;
    } else if (zone === "cave") {
        Music.playing = cave;
    } else if (zone === "title") {
        Music.playing = title;
    }

    if (Music.playing) {
        Music.playing.loop(true);
        Music.playing.play();
    }
}

export function SoundAttack() {
    if (Sounds.swoosh) {
        Sounds.swoosh.play();
    }
}

export function StopAllSounds() {
    if (Sounds.swoosh) swoosh.stop();
    if (Music.title) title.stop();
    if (Music.forest) forest.stop();
    if (Music.cave) cave.stop();
    if (Music.playing) playing.stop();
}