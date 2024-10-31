import { exec } from 'child_process';
import { promises as fs } from 'fs';
import path from 'path';
import { fileURLToPath } from 'url';

// Convert __dirname to work with ESM
const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

// Path to the convert-db-to-base64.js script
const convertScript = path.join(__dirname, 'convert-db-to-base64.js');

// Path to the db.js file
const dbFile = path.join(__dirname, 'db.js');

// Run the convert-db-to-base64.js script
exec(`node ${convertScript}`, async (error, stdout, stderr) => {
    if (error) {
        console.error(`Error executing script: ${error.message}`);
        return;
    }
    if (stderr) {
        console.error(`Error: ${stderr}`);
        return;
    }

    // Capture the base64 output
    const base64Database = stdout.trim();

    try {
        // Read the db.js file
        let data = await fs.readFile(dbFile, 'utf8');

        // Replace the base64Database variable in db.js
        const updatedData = data.replace(
            /const base64Database = '.*';/,
            `const base64Database = '${base64Database}';`
        );

        // Write the updated content back to db.js
        await fs.writeFile(dbFile, updatedData, 'utf8');
        console.log('db.js has been updated with the new base64Database value.');
    } catch (err) {
        console.error(`Error processing db.js: ${err.message}`);
    }
});
