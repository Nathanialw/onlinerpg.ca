'use strict'

import { Get_Unit_Stats, Get_Unit_Name, Get_By_UID } from "../../db/db.js"
import { Update_Screen } from "../../frontend/ui.js"
//get string from server
import { targetHealthBar, Draw_Sprite, Create_Text_Line, Get_Right_Panel_Origin_x, Get_Right_Panel_Origin_y, Load_Target_Image, cellSize, Clear_Target} from "../../graphics/graphics.js"
import { Strip_Leading_Zeroes } from "../../utils/utils.js"
import { Set_Game_Panel_Index } from "../menus/gameMenu.js"

const gender = ["♂", "♀"]
const sex = ["m", "f"]
let lineWidthRight = 36.5;
let lineWidthLeft = 6.5;

function Set_From_Right(textSprite) {
    textSprite.x = textSprite.x - textSprite.width;
}

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
    traits: [],

    Health: 0,
    MaxHealth: 0,
}

export async function Get_Target_Stats_From_Server(statsString) {
    targetStats.target = true;
    targetStats.unitID = Strip_Leading_Zeroes(statsString.substring(0, 3));
    const nameID = Strip_Leading_Zeroes(statsString.substring(3, 7));

    targetStats.age = Strip_Leading_Zeroes(statsString.substring(7, 10));
    const genderIndex = Strip_Leading_Zeroes(statsString.substring(10, 11))
    targetStats.gender = gender[genderIndex];
    targetStats.health = Strip_Leading_Zeroes(statsString.substring(11, 14)) + "/" + Strip_Leading_Zeroes(statsString.substring(14, 17));
    targetStats.Health = parseInt(Strip_Leading_Zeroes(statsString.substring(11, 14)));
    targetStats.MaxHealth = parseInt(Strip_Leading_Zeroes(statsString.substring(14, 17)));

    targetStats.attack = Strip_Leading_Zeroes(statsString.substring(17, 19)) + "-" + Strip_Leading_Zeroes(statsString.substring(19, 21));
    targetStats.AC = Strip_Leading_Zeroes(statsString.substring(21, 23));
    const picNum = Strip_Leading_Zeroes(statsString.substring(23, 25));    
    const numTraits = parseInt(Strip_Leading_Zeroes(statsString.substring(25, 27)));    
    targetStats.traits.length = 0;
    for (let i = 0; i < numTraits; i++) {
        targetStats.traits[i] = Strip_Leading_Zeroes(statsString.substring(27 + (i*3), 30 + (i*3)));
    }

    //query DB using targetStats.unitID
    const name = await Get_Unit_Name(nameID)
    targetStats.name = name.name;
    const stats = await Get_Unit_Stats(targetStats.unitID)
    targetStats.species = stats.name;
    targetStats.speed = stats.speed;
    targetStats.vision = stats.vision;
    targetStats.pic = "assets/graphics/imgs/" + targetStats.species + "/" + sex[genderIndex] + "/" + picNum + ".png";
    targetStats.bio = stats.description;
    targetStats.alignment = stats.alignment;
    
    Set_Game_Panel_Index(0);
    Update_Screen();
}

function Display_Line(value, i, x, y, right = false) {
    targetStatsDisplay[i] = Create_Text_Line(value, cellSize, i, x, y);
    if (right) {
        Set_From_Right(targetStatsDisplay[i])            
    }
    i += 1.1;
    return i;
}

export async function Target_Stats() {
    if (!targetStats.target) {
        return
    }

    //display rect 
    Clear_Target();

    let x = Get_Right_Panel_Origin_x();
    targetStatsDisplay.length = 0;
    let y = Get_Right_Panel_Origin_y()
    Load_Target_Image(x, y , targetStats.pic)        
    let line = 0;

    x = Get_Right_Panel_Origin_x() + 19;
    y = Get_Right_Panel_Origin_y() + 3.5; 
    line = Display_Line(targetStats.species, line, x, y);

    
    x = Get_Right_Panel_Origin_x() + 14;
    y = Get_Right_Panel_Origin_y() + 4; 

    line = Display_Line("Name: " + targetStats.name + targetStats.gender, line, x, y);
    line = Display_Line("Age: " + targetStats.age, line, x, y);
    line = Display_Line("Alignment: " + targetStats.alignment, line, x, y);
    line = Display_Line("Vision: " + targetStats.vision, line, x, y);
    line = Display_Line("Health: " + targetStats.health, line, x, y);
    // display health bar
    const full = 14.5;
    let hpBarWidth = (targetStats.Health / targetStats.MaxHealth) * full;
    Draw_Sprite((x) * cellSize, (line + 4) * cellSize, hpBarWidth * cellSize, 0.75 * cellSize, targetHealthBar);
    
    x = Get_Right_Panel_Origin_x() + 21;
    y = Get_Right_Panel_Origin_y() + 5; 
    line = 0;
    line = Display_Line("", line, x, y);
    line = Display_Line("   Attack: " + targetStats.attack, line, x, y);
    line = Display_Line("       AC: " + targetStats.AC, line, x, y);
    line = Display_Line("    Speed: " + targetStats.speed, line, x, y);
    line = Display_Line("", line, x, y);
    
    // let lines = Math.ceil(targetStats.bio.length/lineWidthRight);
    let currentPos = 0;
    x = Get_Right_Panel_Origin_x() + 14;
    y = Get_Right_Panel_Origin_y() + 6.5;

    // for (let i = 0; i < lines; i++) {
    while (currentPos < targetStats.bio.length) {
        //itertate backwards to find the last space in the line
        // if (targetStats.bio.length < lineWidthRight) {
            // lineWidthRight = targetStats.bio.length
        // }

        //get the lin to print
        let bioLine = targetStats.bio.substring(currentPos, currentPos + lineWidthRight);
        for (let j = bioLine.length; j > 0; j--) {
            if (bioLine[j] === " " || bioLine[j] === "-" || bioLine[j] === "." || bioLine[j] === "," || bioLine[j] === "" || targetStats.bio.length < lineWidthRight) {
                line = Display_Line(targetStats.bio.substring(currentPos, currentPos + j + 1), line, x, y);
                currentPos = currentPos + j + 1;
                break;
            }
        }
    }


    //traits
    x = Get_Right_Panel_Origin_x() + 1.5;
    y = Get_Right_Panel_Origin_y() + 17.25; 

    line = 0
    line = Display_Line("Traits: ", line, x, y);

    x = Get_Right_Panel_Origin_x() + 13;    
    for (let i = 0; i < targetStats.traits.length; i++) {
        const trait = await Get_By_UID("name", "traits", targetStats.traits[i]);
        line = Display_Line(trait.name, line, x, y, true);

        //add mouseover listener
        // targetStatsDisplay[i].interactive = true;
    }


    //get traits from server as IDs and fetch the IDs from the db to get the trait names and descriptions

}