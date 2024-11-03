import { classes } from '../frontend/classes.js';
import { Strip_Leading_Zeroes } from '../utils/utils.js';
import { Update_Screen } from '../frontend/ui.js';
import { Wait_For_Load } from '../graphics/graphics.js';

export let Gender = ["Male", "Female"];
export let UnitClass = ["Fighter", "Mystic"];
export let Alignment = ["Good", "Neutral", "Evil"];
export let Species = [
    "Alp",
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
    "Skeleton",
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
    "Quinotaur",
    "Roc",
    "Satyr",
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
    Mana: 0,
    MaxMana: 0,
    AC: 0,
    Speed: 0,
    MaxSpeed: 0,
    MinDamage: 0,
    MaxDamage: 0,
    
    IceResist: 0,
    FirResist: 0,
    PsnResist: 0,
    ShwResist: 0,
    HlyResist: 0,
    PhyResist: 0,

    XP: 0,
    Level: 0,
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

export async function UpdatePlayerInfo(characterCreate) {
    console.log 
}

export async function Update_Player_Stats(characterCreate) {
    let length = characterCreate.length;
    if (length === 0) {
        return;
    }
    //health/max
    //AC
    //speed/max
    //damage/max
    
    //potrait
    characterInfo.Name = characterCreate.substring(4, length - 34);
    characterInfo.Name = characterInfo.Name.charAt(0).toUpperCase() + characterInfo.Name.slice(1);

    characterInfo.Level = Strip_Leading_Zeroes(characterCreate.substring(length-34, length-32));
    characterInfo.XP = Strip_Leading_Zeroes(characterCreate.substring(length-32, length-30));

    characterInfo.Mana = Strip_Leading_Zeroes(characterCreate.substring(length-30, length-27));
    characterInfo.MaxMana = Strip_Leading_Zeroes(characterCreate.substring(length-27, length-24));


    characterInfo.Potrait = characterCreate.substring(length-24, length-21);
    characterInfo.AC = Strip_Leading_Zeroes(characterCreate.substring(length-21, length-19));
    characterInfo.Age = Strip_Leading_Zeroes(characterCreate.substring(length-19, length-16));
    characterInfo.Health = Strip_Leading_Zeroes(characterCreate.substring(length-16, length-13));
    characterInfo.MaxHealth = Strip_Leading_Zeroes(characterCreate.substring(length-13, length-10));
    characterInfo.Speed = Strip_Leading_Zeroes(characterCreate.substring(length-10, length-9));
    characterInfo.MaxSpeed = Strip_Leading_Zeroes(characterCreate.substring(length-9, length-8));
    characterInfo.MinDamage = Strip_Leading_Zeroes(characterCreate.substring(length-8, length-6));
    characterInfo.MaxDamage = Strip_Leading_Zeroes(characterCreate.substring(length-6, length-4));

    
    let genderIndex = characterCreate.charAt(length-4);
    let gender = Gender[parseInt(genderIndex)]
    if (gender === "Male") {
        characterInfo.Gender = '♂';
    }
    else {
        characterInfo.Gender = '♀';
    }
    let speciesIndex = characterCreate.charAt(length-3);
    let classIndex = characterCreate.charAt(length-2);
    let alignmentIndex = characterCreate.charAt(length-1);

    characterInfo.Species = Species[parseInt(speciesIndex, 10)];
    characterInfo.Class = UnitClass[parseInt(classIndex, 10)];
    characterInfo.Alignment = Alignment[parseInt(alignmentIndex, 10)];

    const key = speciesIndex + genderIndex + classIndex + alignmentIndex;
    characterInfo.HeroClass = classes.get(key) || 'Unknown Class'; // Default to 'Unknown Class' if key is not found
}