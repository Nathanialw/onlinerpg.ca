'use strict';

import { Update } from './receive.js';

const local = "localhost:9002"
const prod = "onlinerpg.ca"

// Function to fetch the session ID from the PHP script
async function getSessionId() {
    try {
        const response = await fetch('session.php');
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        const sessionId = await response.text();
        return sessionId;
    } catch (error) {
        console.error('There was a problem with the fetch operation:', error);
    }
}

// Generate or retrieve the unique identifier (e.g., session ID)
let sessionId; // This should be generated by your server
let websocket;
let reconnectInterval = 500; // 0.5 seconds
let pingInterval;

let reconnectAttempts = 0;
const maxReconnectAttempts = 10;

export async function createWebSocket() {
    sessionId = await getSessionId();
    if (!sessionId) {
        console.error('Failed to retrieve session ID');
        return;
    }

    if (websocket) {
        websocket.onopen = null;
        websocket.onmessage = null;
        websocket.onclose = null;
        websocket.onerror = null;
    }

    let i = 0;

    return new Promise((resolve, reject) => {
        const prod = 'www.onlinerpg.ca'; // Replace with your production domain
        const local = 'localhost:9002'; // Replace with your local domain and port
        
        const isProduction = window.location.hostname === prod;
        const websocketUrl = isProduction 
            ? `wss://${prod}/ws?session_id=${sessionId}` 
            : `ws://${local}/ws?session_id=${sessionId}`;
        
        websocket = new WebSocket(websocketUrl);

        websocket.onopen = () => {
            console.log("WebSocket connection opened");
            reconnectAttempts = 0; // Reset the counter on successful connection

            websocket.onmessage = (event) => {
                if (event.data === '0') {
                    return;
                }

                let type = event.data[0];
                let data = event.data.substring(1);

                if (data.length === 0) {
                    return;
                }
                console.log("Received message type", type, "with data", data);
                // Use a hash map to update
                Update[type](data);
            };

            // Set up ping interval
            pingInterval = setInterval(() => {
                if (websocket.readyState === WebSocket.OPEN) {
                    websocket.send(JSON.stringify({ event: "ping" }));
                }
            }, 2500);

            resolve(); // Resolve the promise when the connection is opened
        };

        websocket.onclose = () => {
            console.log("WebSocket connection closed, attempting to reconnect...");
            clearInterval(pingInterval); // Clear the ping interval

            const connectText = document.getElementById('connect-text');
            if (reconnectAttempts < maxReconnectAttempts) {
                if (connectText) {
                    connectText.textContent = connectText.textContent + '.'
                }
                reconnectAttempts++;
                setTimeout(() => {
                    createWebSocket();
                }, reconnectInterval);
            } else {                
                if (connectText) {
                    connectText.style.color = 'red';
                    connectText.style.display = 'block'; // Show error message
                    connectText.textContent = `Failed to establish connection.`;
                }
                reconnectAttempts = 0;
                console.error(`Failed to reconnect after ${maxReconnectAttempts} attempts.`);                
                reject(new Error(`Failed to reconnect after ${maxReconnectAttempts} attempts.`));
            }
        };

        websocket.onerror = (error) => {
            console.error("WebSocket error:", error);
            websocket.close();
            reject(error);
        };
    });
}

export function socket() {
    if (websocket && websocket.readyState === WebSocket.OPEN) {
        return { websocket: websocket, isConnected: true };
    } else if (websocket && websocket.readyState === WebSocket.CONNECTING) {
        console.log("Connecting WebSocket...");
        return { websocket: websocket, isConnected: false };
    } else if (websocket && (websocket.readyState === WebSocket.CLOSING || websocket.readyState === WebSocket.CLOSED)) {
        console.log("Reconnecting WebSocket...");
        createWebSocket();
        return { websocket: websocket, isConnected: false };
    } else {
        createWebSocket();
        console.log("Reconnecting WebSocket...");
        return { websocket: websocket, isConnected: false };
    }
}

function closeWebSocket() {
    if (websocket) {
        clearInterval(pingInterval); // Clear the ping interval
        websocket.close();
    }
}

export function Send_Web_Socket_Message(message) {
    if (socket().isConnected) {
        socket().websocket.send(message);
    }
}