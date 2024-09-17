
let Gender = ["Male", "Female"];
let UnitClass = ["Fighter", "Mystic"];
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

    characterInfo.Name = characterCreate.substring(4, length - 4);
    characterInfo.Gender = Gender[parseInt(characterCreate.charAt(length-4), 10)];
    characterInfo.Species = Species[parseInt(characterCreate.charAt(length-3), 10)];
    characterInfo.Class = UnitClass[parseInt(characterCreate.charAt(length-2), 10)];
    characterInfo.Alignment = Alignment[parseInt(characterCreate.charAt(length-1), 10)];
        
    //h
    //max health
    //AC
    //speed
    //max speed
    //+damage
    
    console.log(characterInfo);
}