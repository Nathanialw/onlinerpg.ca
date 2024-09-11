'use strict'

var swoosh;

function CreateSound() {
    var sound = new Howl ({
        src: ['../../assets/sounds/swish_2.wav'],
        html5: true
    });
    return sound;
}

export function Init () {
    swoosh = CreateSound();
}

export function SoundPlay(keyName) {
    console.log("SoundPlay");
    swoosh.play;
    return true
}
