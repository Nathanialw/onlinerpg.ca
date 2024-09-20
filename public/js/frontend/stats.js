
//get string from server

export let targetStats = {
    name: "??",
    gender: "??",
    alignment: "??",
    pic: "",
    health: "??/??",
    attack: "??-??",
    AC: "??",
    speed: "??",
    vision: "??",
    bio: "??",
}

export function Get_Target_Stats_From_Server(statsString) {
    stats = "";
    for (let i = 0; i < statsString.length; i++) {
        if (statsString[i] === "_") {
            targetStats.name = statsString.substring(0, i);
            stats = statsString.substring(i + 1);
            break;
        }
    }

    targetStats.gender = stats.substring(0, 1);
    targetStats.alignment = stats.substring(1, 2);
    // pic = stats.substring(2, 3);

    for (let i = 2; i < stats.length - 2; i++) {
        if (stats[i] === "_") {
            targetStats.pic = "assets/goblin/male/" + stats.substring(2, i) + ".jpg";
            stats = stats.substring(i + 1);
            break;
        }
    }

    targetStats.health = stats.substring(0, 2) + " / " + stats.substring(2, 4);
    targetStats.attack = stats.substring(4, 6) + " - " + stats.substring(6, 8);
    targetStats.AC = stats.substring(8, 10);
    targetStats.speed = stats.substring(10, 12);
    targetStats.vision = stats.substring(12, 14);
    targetStats.bio = stats.substring(14);
}