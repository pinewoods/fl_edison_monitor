# For problems on rc.local and the initialization stuck and you can't access by screen command
# First press any keep when the edison is booting and type de command
run do_ota

# Execute this is the ssh is working by localhost but not remote
ifconfig wlan0 down
ifconfig usb0 down
ifconfig wlan0 up
ifconfig usb0 up

#Rode o servico do initialize

#crie um link symbolico na pasta do serviço de initialize
ln -s /home/root/pinewoods/fl_edison_monitor/monitor-yfs201.py monitor-yfs201.py


#Utilize a IDE do Arduino para subir o código device.ino no intel edison
#para rodar o código python rode o script
./monitor-arduino.sh

