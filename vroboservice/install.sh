sudo cp vroboservice.service /etc/systemd/system/
sudo systemctl enable vroboservice.service
sudo systemctl start vroboservice.service
sudo systemctl status vroboservice.service
