'use strict'

export var swoosh;

export function CreateSound() {
    var sound = new Howl ({
        src: ['../../assets/sounds/swish_2.wav'],
        html5: true
    });
    return sound;
}

export function SoundPlay(keyName) {
    console.log("SoundPlay");
    swoosh.play;
    return true
}
