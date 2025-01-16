Thusfar only tested on a lunix machine running Ubuntu

Currently hosted at https://www.onlinerpg.ca

Required libraries:

    sudo apt install libwebsocketpp-dev
    sudo apt install build-essential g++ python3-dev autotools-dev libicu-dev libbz2-dev libboost-all-dev

Run instructions:

    clone the repo
    cd onlinerpg.ca        #Navigate to onlinerpg.ca directory
    chmod +x run.sh        #if you need to add permission for the script
    ./run.sh               #command will:    build   ->  Open a browser at the correct port  ->  Run the backend application
    You may pass a port humber as a argument to, otherwise it will default to port 9010    eg. ./run.sh 10020
