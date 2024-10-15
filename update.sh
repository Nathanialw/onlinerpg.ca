# Check if the correct number of arguments are provided
# if [ "$#" -ne 1 ]; then
#     echo "Usage: $0 <restart_process> "
#     exit 1
# fi

# Assign arguments to variables
RESTART=$1

git checkout -- *
git pull

#thusfar unused
#chmod +x /var/www/onlinerpg.ca/webserver/webserver/webserver
#sudo service rpgwebserver restart
#sudo service rpgwebserver status

chmod +x /var/www/onlinerpg.ca/appserver/release/BrowserRPG
chmod 666 /var/www/onlinerpg.ca/appserver/db/data.db
if [ "$RESTART" == "restart" ]; then
    sudo service rpgserver restart
    sudo service rpgserver status
    bg
fi
# sudo service rpgserver restart