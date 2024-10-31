#!/bin/bash

# Function to handle termination signals
cleanup() {
    echo "Stopping servers..."
    # Add any cleanup commands here
    kill $(jobs -p)
    exit 0
}

# Trap termination signals
trap cleanup SIGINT SIGTERM

# Start the main server in the background
# cd /mnt/BED0BFC1D0BF7DE9/Workspace/onlinerpg.ca/appserver/ || { echo "Failed to change directory"; exit 1; }
# ./release/BrowserRPG &

# Start the PHP built-in server in the background
php -S localhost:9010 -t public &

# Open the default web browser to localhost:9010
xdg-open http://localhost:9010

# Wait for both background processes to finish
wait