
//get string from server
import {Create_Text_Line, Get_Right_Panel_Origin_x, Get_Right_Panel_Origin_y, rightPanelWidth, Load_Target_Image} from "../graphics/graphics.js"

let targetStatsDisplay = []
export let targetStats = {
    target: false,
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
    let stats = "";
    targetStats.target = true;
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
            targetStats.pic = "assets/graphics/imgs/goblin/male/" + stats.substring(2, i) + ".jpg";
            stats = stats.substring(i + 1);
            break;
        }
    }

    targetStats.health = stats.substring(0, 2) + "/" + stats.substring(2, 4);
    targetStats.attack = stats.substring(4, 6) + "-" + stats.substring(6, 8);
    targetStats.AC = stats.substring(8, 10);
    targetStats.speed = stats.substring(10, 11);
    targetStats.vision = stats.substring(11, 13);
    targetStats.bio = stats.substring(13, 50);
    Render_Target_Stats()
}

export function Render_Target_Stats() {
    if (!targetStats.target) {
        return
    }
    targetStatsDisplay = []
    let x = Get_Right_Panel_Origin_x();
    let y = Get_Right_Panel_Origin_y()
    Load_Target_Image(x, y, targetStats.pic)    
    y = Get_Right_Panel_Origin_y() + rightPanelWidth; 
    targetStatsDisplay[0] = Create_Text_Line("Name: " + targetStats.name, 0, x, y);
    targetStatsDisplay[1] = Create_Text_Line("Gender: " + targetStats.gender, 1, x, y);
    targetStatsDisplay[2] = Create_Text_Line("Alignment: " + targetStats.alignment, 2, x, y);
    targetStatsDisplay[3] = Create_Text_Line("Health: " + targetStats.health, 3, x, y);
    targetStatsDisplay[4] = Create_Text_Line("Attack: " + targetStats.attack, 4, x, y);
    targetStatsDisplay[5] = Create_Text_Line("AC: " + targetStats.AC, 5, x, y);
    targetStatsDisplay[6] = Create_Text_Line("Speed: " + targetStats.speed, 6, x, y);
    targetStatsDisplay[7] = Create_Text_Line("Vision: " + targetStats.vision, 7, x, y);
    targetStatsDisplay[8] = Create_Text_Line(targetStats.bio, 8, x, y);
}