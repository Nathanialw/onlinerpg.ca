#!/bin/bash

cleanup() {
    echo "Stopping servers..."
    # Add any cleanup commands here
    kill $(jobs -p)
    exit 0
}

trap cleanup SIGINT SIGTERM

# start the server in the background
# cd /mnt/BED0BFC1D0BF7DE9/Workspace/onlinerpg.ca/appserver/ || { echo "Failed to change directory"; exit 1; }
# ./release/BrowserRPG &

# this is for the PHP to run
php -S localhost:9010 -t public &

# open the default web browser to localhost:9010
xdg-open http://localhost:9010

# should make both close when one is closed
wait