import { Init, Music_Play, StopAllSounds } from "../sound/sound.js";
import { Create_Canvas} from '../graphics/graphics.js';
import { Set_Scale_Queries } from "../graphics/scale.js";
import { Init_Item_Effects } from "../db/itemEffects.js";


//we want this it happen before the game starts
export async function Splash_Screen() {
    await Init();
    Music_Play("forest");
    console.log("ui sprites load start")
    await Create_Canvas();
    console.log("ui sprites loaded")
    Set_Scale_Queries();
    console.log("Splash Screen");
    Init_Item_Effects()

}
Splash_Screen()

export function Close_Game() {
    StopAllSounds();

    document.getElementById('gameCanvas').removeChild(app.canvas);    
    app.destroy(true, {children: true, texture: true, source: true});
        // Create a form element
        const form = document.createElement('form');
        form.method = 'post';
    
        // Create an input element
        const input = document.createElement('input');
        input.type = 'submit';
        input.name = 'restartGame';
        input.id = 'restartGame';
        input.className = 'wrapper btn btn-submit';
        input.value = 'Restart Game';
    
        // Append the input to the form
        form.appendChild(input);
    
        // Append the form to the gameCanvas
        document.getElementById('gameCanvas').appendChild(form);    
}

