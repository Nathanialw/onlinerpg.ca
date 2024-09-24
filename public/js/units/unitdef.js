
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
    characterInfo.Name = characterCreate.substring(4, length - 27);



    characterInfo.Potrait = characterCreate.substring(length-26, 1), 10;
    characterInfo.Age = characterCreate.substring(length-25, 3), 10;
    characterInfo.Health = characterCreate.substring(length-22, 3), 10;
    characterInfo.MaxHealth = characterCreate.substring(length-19, 3), 10;
    characterInfo.AC = characterCreate.substring(length-16, 2), 10;
    characterInfo.Speed = characterCreate.substring(length-14, 1), 10;
    characterInfo.MaxSpeed = characterCreate.substring(length-13, 1), 10;
    characterInfo.MinDamage = characterCreate.substring(length-10, 3), 10;
    characterInfo.MaxDamage = characterCreate.substring(length-7, 3), 10;
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