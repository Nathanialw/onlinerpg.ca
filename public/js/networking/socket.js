'use strict';


let websocket;
let reconnectInterval = 1000; // 1 second

function createWebSocket() {
    if (!websocket) {
        //create a new websocket
        websocket = new WebSocket("ws://www.onlinerpg.ca/ws");
    } else {
        //websocket is already exists
        return
    }

    websocket.onopen = () => {
        console.log("WebSocket connection opened");
    };

    websocket.onclose = () => {
        console.log("WebSocket connection closed, attempting to reconnect...");
        setTimeout(() => {
            createWebSocket();
        }, reconnectInterval);
    };

    websocket.onerror = (error) => {
        console.error("WebSocket error:", error);
        websocket.close();
    };

    websocket.onmessage = (event) => {
        console.log("WebSocket message received:", event.data);
        // Handle incoming messages here
    };

    setInterval(() => {
        if (websocket.readyState === WebSocket.OPEN) {
            websocket.send(JSON.stringify({ event: "ping" }));
        }
    }, 2500);
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

export function closeWebSocket() {
    if (websocket) {
        websocket.close();
    }
}