import { Init, Music_Play, StopAllSounds } from "../sound/sound.js";
import { Create_Canvas} from '../graphics/graphics.js';
import { Actions } from "../input/action/action.js";
import { handleMediaQueryChange } from "../graphics/scale.js";


async function Splash_Screen() {
    Init();
    Music_Play("forest");
    await Create_Canvas();
    Actions(" ");
    // handleMediaQueryChange(); // Initial check
    console.log("Splash Screen");
}

await Splash_Screen()

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
