
let Gender = ["Male", "Female"];
let Class = ["Fighter", "Mystic"];
let Alignment = ["Good", "Neutral", "Evil"];
let Species = [
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
    Species: "default",
    Class: "default",
    Alignment: "default",
}
    

export function UpdatePlayerInfo(characterCreate) {
    let length = characterCreate.length;
    console.log("received characterInfo: ", characterCreate);

    let name = characterCreate.substring(4, length - 4);
    console.log(name)
    let gender = parseInt(characterCreate.charAt(length-2), 10);
    console.log(gender);
    let species = parseInt(characterCreate.charAt(length-1), 10);
    console.log(species);
    let unitClass = parseInt(characterCreate.charAt(length), 10);
    console.log(unitClass);
    let alignment = parseInt(characterCreate.charAt(length+1), 10);
    console.log(alignment);

    characterInfo.Name = name;
    characterInfo.Gender = Gender[gender];
    characterInfo.Species = Species[species];
    characterInfo.Class = Class[unitClass]
    characterInfo.Alignment = Alignment[alignment];
        
    //h
    //max health
    //AC
    //speed
    //max speed
    //+damage
    
    console.log(characterInfo);
}