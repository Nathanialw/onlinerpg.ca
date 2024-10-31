import { createWebSocket } from '/js/networking/socket.js';
import { Init_Title, Music_Play } from '../sound/sound.js';
import { character_Create } from './newGame.js';
import { Quit, Resume } from '../game/game.js';


document.getElementById('connectButton').addEventListener('click', async (event) => {
    await Init_Title();    
    Music_Play("title");
    

    const connectError = document.getElementById('nameError');
    const connectText = document.getElementById('connect-text');
    
    connectError.style.display = 'none'; // Hide error message
    connectText.classList.add('connect-text'); // Add error class to input
    connectText.style.color = 'white';
    connectText.textContent = `Connecting...`;
    connectText.style.display = 'block'; // Show error message
    try {
        await createWebSocket();
        
        const connectButton = document.querySelector('#connectButton');
        document.removeEventListener('keydown', connectKeyDown);
        // remove connect button
        if (connectButton) {
            connectButton.remove();
            connectText.style.display = 'none'; // Show error message
        }

        // add New Game button
        const newGameButton = document.createElement('button');
        newGameButton.id = 'newGame';
        newGameButton.classList.add('btn', 'btn-center');
        newGameButton.textContent = 'New Game';        

        //append as first child
        const menuButtons = document.querySelector('.menuButtons');
        if (menuButtons) {
            menuButtons.insertBefore(newGameButton, menuButtons.firstChild);
        } else {
            console.error("Element with class 'menuButtons' not found.");
        }        
        
        Resume();

        //close connection
        const exitButton = document.createElement('button');
        exitButton.id = 'exitGame';
        exitButton.classList.add('btn', 'btn-center');
        exitButton.textContent = 'Exit';        

        //append as adjecent sibling of newGameButton
        menuButtons.insertBefore(exitButton, newGameButton.nextSibling);


        //add event listener to new game button
        const startNewGame = async (event) => {
            const description = document.querySelector('.splashContent');
            if (description) {
                description.remove();
            }        
            
            document.removeEventListener('keydown', gameMenuKeyDown);
            // newGameButton.removeEventListener('click', startNewGame);
            // exitButton.removeEventListener('click', exitGame);
            const newGameButton = document.querySelector('#newGame');
            if (newGameButton) {
                newGameButton.remove();
            }
            character_Create();                
            console.log("New Game button clicked")
        };
        newGameButton.addEventListener('click', startNewGame)

        const exitGame = (event) => {
            console.log("Disconnecting from server and exiting game");
            //send message to server to disconnect
            document.removeEventListener('keydown', gameMenuKeyDown);
            // newGameButton.removeEventListener('click', startNewGame);
            // exitButton.removeEventListener('click', exitGame);
            Quit();
        };
        exitButton.addEventListener('click', exitGame)

        const gameMenuKeyDown = (event) => {
            if (event.key === 'Enter') {
                newGameButton.click();
            }
            else if (event.key === 'Escape') {
                exitButton.click();
            }
        }; 
        document.addEventListener('keydown', gameMenuKeyDown);
    
    } catch (error) {
        console.error("Failed to establish WebSocket connection:", error);
    }
    
});

const connectKeyDown = (event) => {
    if (event.key === 'Enter') {
        document.querySelector('#connectButton').click();
    }
};
document.addEventListener('keydown', connectKeyDown);