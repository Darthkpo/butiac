#!/bin/sh
if [ “$(id -u)” != “0” ]; then
	echo "Se necesitan permisos de superusuario." 2>&1
	exit 1
fi
echo "Para que el driver se pueda comunicar con la placa se necesitan permisos extra, este script los instalara."
while true; do
    read -p "Desea continuar? [s/n]: " sn
    case $sn in
        [Ss]* ) cp butia.rules /etc/udev/rules.d/butia.rules; break;;
        [Nn]* ) exit;;
        * ) echo "Por favor ingrese 's' o 'n'.";;
    esac
done

sudo udevadm trigger #reload udev rules
