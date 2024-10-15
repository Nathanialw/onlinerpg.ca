#!/bin/bash

# Check if the correct number of arguments are provided
RESTART="norestart"
if [ "$#" -ne 1 ]; then
    RESTART=$1
fi

# Assign arguments to variables

git checkout -- *
git pull

#thusfar unused
#chmod +x /var/www/onlinerpg.ca/webserver/webserver/webserver
#sudo service rpgwebserver restart
#sudo service rpgwebserver status

chmod +x /var/www/onlinerpg.ca/appserver/release/BrowserRPG
chmod +x /var/www/onlinerpg.ca/update.sh
chmod 666 /var/www/onlinerpg.ca/appserver/db/data.db

if [ "$RESTART" = "restart" ]; then
    sudo service rpgserver restart
    sudo service rpgserver status
    bg
fi
# sudo service rpgserver restart