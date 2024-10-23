import { createWebSocket } from '/js/networking/socket.js';
import { Init_Title, Music_Play } from '../sound/sound.js';
import { character_Create } from './newGame.js';

document.getElementById('connect').addEventListener('click', async (event) => {
    Init_Title();
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
        const connectButton = document.querySelector('#connect');
        // remove connect button
        if (connectButton) {
            connectButton.remove();
            connectText.style.display = 'none'; // Show error message
        }
        // add New Game button
        const newGameButtonSecion = document.createElement('newGameButton');
        newGameButtonSecion.classList.add('button main-btn');
        document.querySelector('.connectButton').appendChild(newGameButtonSecion);
        
        const newGameButton = document.createElement('button');
        newGameButton.id = 'newGame';
        newGameButton.classList.add('btn', 'btn-center');
        newGameButton.textContent = 'New Game';        
        newGameButtonSecion.appendChild(newGameButton);
        
        //add event listener to new game button
        document.getElementById('newGame').addEventListener('click', async (event) => {
            const description = document.querySelector('.splashContent');
            if (description) {
                description.remove();
            }        
            const newGameButton = document.querySelector('#newGame');
            if (newGameButton) {
                newGameButton.remove();
            }
            character_Create();                
            console.log("New Game button clicked")
        })

        // //add resume button 
        // if (1) { send a message to the server to check if there is a saved game
        //     const resumeButton = document.createElement('button');
        //     resumeButton.id = 'resume';
        //     resumeButton.classList.add('btn', 'btn-center');
        //     resumeButton.textContent = 'Resume';
        //     newGameButton.appendChild(resumeButton);

        //     //add event listener to resume button
        //     document.getElementById('resume').addEventListener('click', async (event) => {
        //     //send message to server to resume game
        //     console.log("Resume button clicked")
        // }

        //close connection
    
    } catch (error) {
        console.error("Failed to establish WebSocket connection:", error);
    }
    
});

