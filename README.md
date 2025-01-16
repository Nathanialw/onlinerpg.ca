Thusfar only tested on a lunix machine running Ubuntu

Currently hosted at https://www.onlinerpg.ca

Required libraries:

    -sudo apt install libwebsocketpp-dev
    -sudo apt install build-essential g++ python3-dev autotools-dev libicu-dev libbz2-dev libboost-all-dev

Run instructions:

    -Navigate to onlinerpg.ca directory
    -./run.sh #command will:    build   ->  Open a browser at the correct port  ->  Run the backend application
    -You may pass a port humber as a argument, otherwise it will default to port 9010
