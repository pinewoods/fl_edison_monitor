# For problems on rc.local and the initialization stuck and you can't access by screen command
# First press any keep when the edison is booting and type de command
run do_ota


# If the ssh service and ping is not working and the only way to access the edison is only by screen
# probably is an IP conflict, e.g. 192.168.2.15 (default address for usb0) and 192.168.2.x (your wlan0 IP)
# change the default ip on usb0 configuration file.
vi /etc/systemd/network/usb0.network 

#in the file change the ip for something like this:
[Match]
Name=usb0

[Network]
Address=192.168.99.15/24

#Rode o servico do initialize

#crie um link symbolico na pasta do serviço de initialize
ln -s /home/root/pinewoods/fl_edison_monitor/monitor-yfs201.py monitor-yfs201.py


#Utilize a IDE do Arduino para subir o código device.ino no intel edison


#Para rodar o código python rode o script
./monitor-arduino.sh

#Para adicionar o código na inicialização faça um link para pasta de init

cd /etc/init.d/

#Crie o link

ln -s ~/pinewoods/fl_edison_monitor/pine-start.sh pine-start.sh

#Adicione a permissao
chmod +x pine-start.sh 

cd /etc/init.d/

#adicione no rc defaults
update-rc.d pine-start.sh defaults


