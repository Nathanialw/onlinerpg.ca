'use strict'

import { Update_Screen } from "../../frontend/ui.js"
//get string from server
import {Create_Text_Line, Get_Right_Panel_Origin_x, Get_Right_Panel_Origin_y, Load_Target_Image, minimapCellSize, Clear_Target} from "../../graphics/graphics.js"
import { Set_Game_Panel_Index } from "../menus/gameMenu.js"

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
    targetStats.bio = stats.substring(15);
    
    Set_Game_Panel_Index(0);
    Update_Screen();
}

function Display_Line(value, i, x, y) {
    targetStatsDisplay[i] = Create_Text_Line(value, minimapCellSize, i, x, y);
    i++;
    return i;
}

export function Target_Stats() {
    if (!targetStats.target) {
        return
    }

    //display rect 
    Clear_Target();


    let x = Get_Right_Panel_Origin_x() + 1.8;
    targetStatsDisplay.length = 0;
    let y = Get_Right_Panel_Origin_y() + 1.4
    Load_Target_Image(x - 1, y + 3, targetStats.pic)        
    
    x = Get_Right_Panel_Origin_x() + 18.3;
    y = Get_Right_Panel_Origin_y() + 6; 

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
    line = Display_Line("", line, x, y);
    let lineWidth = 24;
    // let lines = Math.ceil(targetStats.bio.length/lineWidth);
    let currentPos = 0;

    x = Get_Right_Panel_Origin_x() + 1.3;
    y = Get_Right_Panel_Origin_y() + 13.4; 

    // for (let i = 0; i < lines; i++) {
    while (currentPos < targetStats.bio.length) {
        //itertate backwards to find the last space in the line
        let bioLine = targetStats.bio.substring(currentPos, currentPos + lineWidth);
        for (let j = bioLine.length; j > 0; j--) {
            if (bioLine[j] === " " || bioLine[j] === "-" || bioLine[j] === "." || bioLine[j] === ",") {
                line = Display_Line(targetStats.bio.substring(currentPos, currentPos + j + 1), line, x, y);
                currentPos = currentPos + j + 1;
                break;
            }
        }
    }


    //traits
    x = Get_Right_Panel_Origin_x() + 14.3;
    y = Get_Right_Panel_Origin_y() + 13;
    line = 0
    line = Display_Line("Traits: ", line, x, y);

    //get traits from server as IDs and fetch the IDs from the db to get the trait names and descriptions

}