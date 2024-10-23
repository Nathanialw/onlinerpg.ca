'use strict'

import { Get_Item_Stats } from "../../db/db.js"
import { Update_Screen } from "../../frontend/ui.js"
//get string from server
import {Create_Text_Line, Get_Right_Panel_Origin_x, Get_Right_Panel_Origin_y, Load_Target_Image, minimapCellSize, Clear_Target} from "../../graphics/graphics.js"
import { Strip_Leading_Zeroes } from "../../utils/utils.js"
import { Set_Game_Panel_Index } from "../menus/gameMenu.js"

let targetStatsDisplay = []
export let targetStats = {
    target: false,
    name: "??",
    species: "??",
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
    targetStats.target = true;
    targetStats.unitID = Strip_Leading_Zeroes(statsString.substring(0, 3));
    targetStats.name = Strip_Leading_Zeroes(statsString.substring(3, 6));

    targetStats.age = Strip_Leading_Zeroes(statsString.substring(6, 9));
    targetStats.gender = Strip_Leading_Zeroes(statsString.substring(9, 10));
    targetStats.health = Strip_Leading_Zeroes(statsString.substring(10, 13)) + "/" + Strip_Leading_Zeroes(statsString.substring(13, 16));
    targetStats.attack = Strip_Leading_Zeroes(statsString.substring(16, 18)) + "-" + Strip_Leading_Zeroes(statsString.substring(18, 20));
    targetStats.AC = Strip_Leading_Zeroes(statsString.substring(20, 22));
        
    //query DB using targetStats.unitID
    Get_Item_Stats(targetStats.unitID).then((data) => {
        targetStats.species = data.name;
        targetStats.speed = data.speed;
        targetStats.vision = data.vision;
        targetStats.pic = data.image;
        targetStats.bio = data.description;
        targetStats.alignment = data.alignment;
        Set_Game_Panel_Index(0);
        Update_Screen();
    }).catch((error) => {
        console.error("Error fetching item stats:", error);
    });

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