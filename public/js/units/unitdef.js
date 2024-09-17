
let Gender = ["male", "Female"];
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
}
    

export function UpdatePlayerInfo(characterCreate) {
    let length = characterCreate.length;
    console.log("received characterInfo: ", characterCreate);

    characterInfo = {
        Name: characterCreate.substring(4, length - 4),
        Gender: Gender[parseInt(characterCreate.charAt(length-3), 10)],
        Species: Species[parseInt(characterCreate.charAt(length-2), 10)],
        Class: Class[parseInt(characterCreate.charAt(length-1), 10)],
        Alignment: Alignment[parseInt(characterCreate.charAt(length), 10)]
        //health
        //max health
        //AC
        //speed
        //max speed
        //+damage
    }
    console.log(characterInfo);
}