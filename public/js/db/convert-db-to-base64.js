const fs = require('fs');

// Path to your SQLite database file
const dbFilePath = '../../db/data.db';

// Read the SQLite database file
const dbFileBuffer = fs.readFileSync(dbFilePath);

// Convert the file buffer to a base64 string
const base64Database = dbFileBuffer.toString('base64');

// Log the base64 string (you can copy this string to your JavaScript code)
console.log(base64Database);