#!/bin/bash

# Check if the correct number of arguments are provided
RESTART="norestart"
if [ "$#" -eq 1 ]; then
    RESTART=$1
fi

# Pull the latest changes from the repository
git checkout -- *
git pull

# Make necessary files executable and set permissions
chmod +x /var/www/onlinerpg.ca/appserver/release/BrowserRPG
chmod 666 /var/www/onlinerpg.ca/appserver/db/data.db

# Restart the rpgserver service if the argument is "restart"
if [ "$RESTART" = "-r" ]; then
    echo "Restarting rpgserver service..."
    sudo service rpgserver restart
    timeout 0.5s sudo service rpgserver status
fi