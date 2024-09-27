import {classes} from './classes.js';

export let Gender = ["Male", "Female"];
export let UnitClass = ["Fighter", "Mystic"];
export let Alignment = ["Good", "Neutral", "Evil"];
export let Species = [
    "Alpaca",
    "Basilisk",
    "Centaur",
    "Dwarf",
    "Elf",
    "Fox",
    "Goblin",
    "Human",
    "Iguana",
    "Jackal",
    "Kobold",
    "Lamia",
    "Minotaur",
    "Nymph",
    "Orc",
    "Pixie",
    "Qat",
    "Rat",
    "Satyr",
    "Treant",
    "Unicorn",
    "Valkyrie",
    "Warg",
    "Xana",
    "Yale",
    "Zombie",
    "Angel",
    "Byakhee",
    "Chimera",
    "Dragon",
    "Ebon",
    "Fairy",
    "Golem",
    "Harpy",
    "Imp",
    "Jinn",
    "Kraken",
    "Lich",
    "Madusa",
    "Naga",
    "Ogre",
    "Poltergeist",
    "Qaffir",
    "Roc",
    "Siren",
    "Troll",
    "Urias",
    "Vampire",
    "Witch",
    "Xanthus",
    "Yeti",
    "Ziburinis"
]

export let characterInfo = {
    Name: "Player",
    Gender: "default",
    HeroClass: "default",
    Species: "default",
    Class: "default",
    Alignment: "default",
    Potrait: "default",

    Age: 0,
    Health: 0,
    MaxHealth: 0,
    AC: 0,
    Speed: 0,
    MaxSpeed: 0,
    MinDamage: 0,
    MaxDamage: 0,
}
    

//need two functions
//one to set the static player stats
    //name
    //gender
    //species
    //class
    //alignment
    //portrait
//one to update the variable player stats
    //health/max
    //AC
    //speed/max
    //damage/max
    
    //level 
    //exp

export function UpdatePlayerInfo(characterCreate) {
    let length = characterCreate.length;
    console.log("received characterInfo: ", characterCreate);

    //health/max
    //AC
    //speed/max
    //damage/max
    
    //potrait
    characterInfo.Name = characterCreate.substring(4, length - 24);

    characterInfo.Potrait = characterCreate.substring(length-24, length-21);
    characterInfo.AC = characterCreate.substring(length-21, length-19);
    characterInfo.Age = characterCreate.substring(length-19, length-16);
    characterInfo.Health = characterCreate.substring(length-16, length-13);
    characterInfo.MaxHealth = characterCreate.substring(length-13, length-10);
    characterInfo.Speed = characterCreate.substring(length-10, length-9);
    characterInfo.MaxSpeed = characterCreate.substring(length-9, length-8);
    characterInfo.MinDamage = characterCreate.substring(length-8, length-6);
    characterInfo.MaxDamage = characterCreate.substring(length-6, length-4);
    let genderIndex = characterCreate.charAt(length-4);
    let gender = Gender[parseInt(genderIndex)]
    if (gender === "Male") {
        characterInfo.Gender = '♂';
    }
    else if (gender === "Female") {
        characterInfo.Gender = '♀';
    }
    let speciesIndex = characterCreate.charAt(length-3);
    let classIndex = characterCreate.charAt(length-2);
    let alignmentIndex = characterCreate.charAt(length-1);

    let Species = Species[parseInt(speciesIndex, 10)];
    let Class = UnitClass[parseInt(classIndex, 10)];
    let Alignment = Alignment[parseInt(alignmentIndex, 10)];
        


    const key = speciesIndex + genderIndex + classIndex + alignmentIndex;
    characterInfo.HeroClass = classes.get(key) || 'Unknown Class'; // Default to 'Unknown Class' if key is not found
    //h
    //max health
    //AC
    //speed
    //max speed
    //+damage
    
    console.log(characterInfo);
}