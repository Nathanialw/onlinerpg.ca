import fs from 'fs';

// Path to your SQLite database file
const dbFilePath = 'appserver/db/data.db';

// Read the SQLite database file
const dbFileBuffer = fs.readFileSync(dbFilePath);

// Convert the file buffer to a base64 string
const base64Database = dbFileBuffer.toString('base64');

// Log the base64 string (you can copy this string to your JavaScript code)
console.log(base64Database);

//run with:        node --experimental-modules convert-db-to-base64.mjs
