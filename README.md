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


# Utilize a IDE do Arduino para subir o código device.ino no intel edison
# Ou para subir remotamente o sketch primeiro abra a IDE do arduino

# No edison antes de mais nada, delete ou faça um backup do sketch.elf antigo

# Va em Preferences e habilite o verbose para compilation
# Compile o código e verifique onde a IDE salvou o .elf do seu código

# Faça um mv do seu .elf para sketch.elf e por fim faça o scp

mv device.cpp.elf sketch.elf

scp sketch.elf root@192.168.2.101:/sketch/sketch.elf

# Acesse o Edison e adicione a permissão:

chmod +x sketch.elf


#Para rodar o código python rode o script
./monitor-arduino.sh

#Para adicionar o código na inicialização faça um link para pasta de init

cp pinewoods.service /lib/systemd/system/

cd /lib/systemd/system

#Adicione a permissao
chmod +x pinewoods.service 

#habilite o service no system init
systemctl enable pinewoods.service 



