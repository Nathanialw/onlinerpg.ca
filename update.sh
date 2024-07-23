chmod +x update.sh
git checkout -- *
git pull
chmod +x /var/www/onlinerpg.ca/webserver/webserver/webserver
sudo service rpgwebserver restart
sudo service rpgwebserver status