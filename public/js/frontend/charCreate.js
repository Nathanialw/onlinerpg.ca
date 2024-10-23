import { createWebSocket, socket, Send_Web_Socket_Message } from '/js/networking/socket.js';
import { classes } from '/js/frontend/classes.js';
import { Init_Title, Music_Play } from '../sound/sound.js';
import { character_Create } from './newGame.js';




document.getElementById('connect').addEventListener('click', async (event) => {
    const connectError = document.getElementById('nameError');
    const connectText = document.getElementById('connect-text');
    
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
        }
        // add New Game button
        const newGameButton = document.createElement('button');
        newGameButton.id = 'newGame';
        newGameButton.classList.add('btn', 'btn-center');
        newGameButton.textContent = 'New Game';        
        document.querySelector('.connectButton').appendChild(newGameButton);
        
        //add event listener to new game button
        document.getElementById('newGame').addEventListener('click', async (event) => {
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
    
    } catch (error) {
        console.error("Failed to establish WebSocket connection:", error);
        connectError.textContent = `Failed to establish connection.`;
    }
});



// let species = ["human", "elf"];

