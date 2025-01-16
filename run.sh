#!/bin/bash
cd appserver
mkdir release
cd release
cmake ..
make
cd ..
cd ..

cleanup() {
    echo "Stopping servers..."
    kill $(jobs -p)
    exit 0
}

trap cleanup SIGINT SIGTERM

#checking it the arguemnt is a valid port number
if [[ "$1" =~ ^[0-9]+$ ]] && [ "$1" -ge 1 ] && [ "$1" -le 65535 ]; then
    port=$1
else
    echo "Invalid port number. Please provide a port number between 1 and 65535. Defaulting to 9010."
    port=9010
fi

# this is for the PHP to run
php -S localhost:$port -t public &

# start the server in the background
cd appserver || { echo "Failed to change directory"; exit 1; }
./release/BrowserRPG &

# open the default web browser to localhost:$port
xdg-open http://localhost:$port

# should make both close when one is closed
wait