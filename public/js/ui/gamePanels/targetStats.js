'use strict'

import { Get_Unit_Stats, Get_Unit_Name } from "../../db/db.js"
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

export async function Get_Target_Stats_From_Server(statsString) {
    targetStats.target = true;
    targetStats.unitID = Strip_Leading_Zeroes(statsString.substring(0, 3));
    const nameID = Strip_Leading_Zeroes(statsString.substring(3, 7));

    targetStats.age = Strip_Leading_Zeroes(statsString.substring(7, 10));
    targetStats.gender = Strip_Leading_Zeroes(statsString.substring(10, 11));
    targetStats.health = Strip_Leading_Zeroes(statsString.substring(11, 14)) + "/" + Strip_Leading_Zeroes(statsString.substring(14, 17));
    targetStats.attack = Strip_Leading_Zeroes(statsString.substring(17, 19)) + "-" + Strip_Leading_Zeroes(statsString.substring(19, 21));
    targetStats.AC = Strip_Leading_Zeroes(statsString.substring(21, 23));
        
    //query DB using targetStats.unitID
    const stats = await Get_Unit_Stats(targetStats.unitID)
    const name = await Get_Unit_Name(nameID)
    targetStats.name = name.name;
    targetStats.species = stats.name;
    targetStats.speed = stats.speed;
    targetStats.vision = stats.vision;
    targetStats.pic = "assets/graphics/imgs/" + stats.image;
    targetStats.bio = stats.description;
    targetStats.alignment = stats.alignment;
    
    Set_Game_Panel_Index(0);
    console.log("refreshing screen")
    Update_Screen();
    console.log("done")
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

    console.log("displaying target stats2", targetStats)
    let x = Get_Right_Panel_Origin_x() + 1.8;
    targetStatsDisplay.length = 0;
    let y = Get_Right_Panel_Origin_y() + 1.4
    Load_Target_Image(x - 1, y + 3, targetStats.pic)        
    
    x = Get_Right_Panel_Origin_x() + 18.3;
    y = Get_Right_Panel_Origin_y() + 6; 

    let line = 0;
    console.log("displaying target stats3")
    line = Display_Line("Name: " + targetStats.name, line, x, y);
    line = Display_Line("Species: " + targetStats.species, line, x, y);
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
    console.log("displaying target stats4")
    x = Get_Right_Panel_Origin_x() + 1.3;
    y = Get_Right_Panel_Origin_y() + 13.4; 

    // for (let i = 0; i < lines; i++) {
    console.log("displaying target stats5")
    while (currentPos < targetStats.bio.length) {
        //itertate backwards to find the last space in the line
        // if (targetStats.bio.length < lineWidth) {
            // lineWidth = targetStats.bio.length
        // }

        //get the lin to print
        let bioLine = targetStats.bio.substring(currentPos, currentPos + lineWidth);
        
        for (let j = bioLine.length; j > 0; j--) {
            if (bioLine[j] === " " || bioLine[j] === "-" || bioLine[j] === "." || bioLine[j] === "," || bioLine[j] === "") {
                line = Display_Line(targetStats.bio.substring(currentPos, currentPos + j + 1), line, x, y);
                currentPos = currentPos + j + 1;
                console.log("currentPos:", currentPos, "targetStats.bio.length:", targetStats.bio.length)
                break;
            }
            console.log(currentPos, targetStats.bio.length)
            console.log(j, bioLine)
        }
    }


    //traits
    x = Get_Right_Panel_Origin_x() + 14.3;
    y = Get_Right_Panel_Origin_y() + 13;
    line = 0
    line = Display_Line("Traits: ", line, x, y);

    //get traits from server as IDs and fetch the IDs from the db to get the trait names and descriptions

}