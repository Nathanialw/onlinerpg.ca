Tested for lunix running Ubuntu

Currently hosted at https://www.onlinerpg.ca

Required libraries:

    sudo apt install update
    sudo apt install cmake
    sudo apt install libwebsocketpp-dev
    sudo apt install build-essential g++ python3-dev autotools-dev libicu-dev libbz2-dev libboost-all-dev
    sudo apt install php
    sudo apt install xdg-install

Run instructions:

    git clone git@github.com:Nathanialw/RPG-old.git     #clone the repo
    cd onlinerpg.ca                                     #Navigate to onlinerpg.ca directory
    chmod +x run.sh                                     #if you need to add permission for the script
    ./run.sh                                            #command will:    build   ->  Open a browser at the correct port  ->  Run the backend application

You may pass a port humber as a argument to, otherwise it will default to port 9010    eg. ./run.sh 10020

It will also work with WSL on windows 10 everything same as above.

Issues:
    If xdg-open gives an error that it cannot find a default browser, assuming you use the default port you can manually go to localhost:9010