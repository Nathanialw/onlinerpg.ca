'use strict';

function loadSqlJsLibrary(callback) {
    const script = document.createElement('script');
    script.src = "/js/libs/sql-wasm.js";
    script.onload = callback;
    document.head.appendChild(script);
}

function Load_DB() {
    const fs = require('fs');
    // Path to your SQLite database file
    const dbFilePath = '../../db/data.db';
    // Read the SQLite database file
    const dbFileBuffer = fs.readFileSync(dbFilePath);
    // Convert the file buffer to a base64 string
    const base64Database = dbFileBuffer.toString('base64');
    // Log the base64 string (you can copy this string to your JavaScript code)
    console.log(base64Database);    
    return base64Database;
}

// Function to convert base64 to Uint8Array
function base64ToUint8Array(base64) {
    const binaryString = atob(base64);
    const len = binaryString.length;
    const bytes = new Uint8Array(len);
    for (let i = 0; i < len; i++) {
        bytes[i] = binaryString.charCodeAt(i);
    }
    return bytes;
}

// Initialize the database after the library is loaded
loadSqlJsLibrary(() => {
    initSqlJs().then(function(SQL) {
        let base64Database = Load_DB();
        // Convert base64 to Uint8Array
        const dbData = base64ToUint8Array(base64Database);

        // Load the existing database
        const db = new SQL.Database(dbData);

        // Query the data
        const result = db.exec("SELECT * FROM test");

        // Log the result
        console.log(result);
    });
});