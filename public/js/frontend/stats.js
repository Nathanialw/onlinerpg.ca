
//get string from server
import {Create_Text_Line, Get_Right_Panel_Origin_x, Get_Right_Panel_Origin_y, Load_Target_Image, Get_Right_Panel_Width} from "../graphics/graphics.js"

let targetStatsDisplay = []
export let targetStats = {
    target: false,
    name: "??",
    age: "??",
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

    targetStats.age = stats.substring(0, 3);
    targetStats.gender = stats.substring(3, 4);
    targetStats.alignment = stats.substring(4, 5);
    // pic = stats.substring(2, 3);

    for (let i = 5; i < stats.length - 5; i++) {
        if (stats[i] === "_") {
            targetStats.pic = "assets/graphics/imgs/goblin/male/" + stats.substring(5, i) + ".jpg";
            stats = stats.substring(i + 1);
            break;
        }
    }

    targetStats.health = stats.substring(0, 3) + "/" + stats.substring(3, 6);
    targetStats.attack = stats.substring(6, 8) + "-" + stats.substring(8, 10);
    targetStats.AC = stats.substring(10, 12);
    targetStats.speed = stats.substring(12, 13);
    targetStats.vision = stats.substring(13, 15);
    targetStats.bio = stats.substring(15, Get_Right_Panel_Width()/12);
    Render_Target_Stats()
}

function Display_Line(value, i, x, y) {
    targetStatsDisplay[i] = Create_Text_Line(value, 12, i, x, y);
    i++;
    return i;
}

export function Render_Target_Stats() {
    if (!targetStats.target) {
        return
    }
    targetStatsDisplay = []
    let x = Get_Right_Panel_Origin_x();
    let y = Get_Right_Panel_Origin_y()
    Load_Target_Image(x, y, targetStats.pic)    
    y = Get_Right_Panel_Origin_y() + 10; 

    let line = 0;
    line = Display_Line("Name: " + targetStats.name, line, x, y);
    line = Display_Line("Age: " + targetStats.age, line, x, y);
    line = Display_Line("Gender: " + targetStats.gender, line, x, y);
    line = Display_Line("Alignment: " + targetStats.alignment, line, x, y);
    line = Display_Line("Health: " + targetStats.health, line, x, y);
    line = Display_Line("Attack: " + targetStats.attack, line, x, y);
    line = Display_Line("AC: " + targetStats.AC, line, x, y);
    line = Display_Line("Speed: " + targetStats.speed, line, x, y);
    line = Display_Line("Vision: " + targetStats.vision, line, x, y);

    let width = Get_Right_Panel_Width()/12;
    let lines = Math.ceil(targetStats.bio.length/width);
    
    for (let i = 0; i < lines; i++) {
        line = Display_Line(targetStats.bio.substring(width * i, (width * i) + width), line, x, y);
    }
}