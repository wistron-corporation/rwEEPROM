#!/usr/bin/env bash

#################################
# Update Author:   Andy YF Wang #
# Update Date  :   2020/05/14   #
# Ver.  :   1.0.0               #
#################################


##copy the eeprom binary & vpddata.json to /home/root/
cp -p /sys/bus/i2c/devices/8-0050/eeprom /home/root/
cp -p /usr/bin/vpddata.json /home/root/


## Get MAC0 via BMC's REST command ##	
printf "\n > Get BMC MAC0 addresses via busctl command."
eth0_mac=$(busctl get-property xyz.openbmc_project.Network /xyz/openbmc_project/network/eth0 xyz.openbmc_project.Network.MACAddress MACAddress |sed 's/^...//;s/.$//;s/\://;s/\://;s/\://;s/\://;s/\://')
if [ "${#eth0_mac}" -ne 12 ]; then
	eth0_mac=0$eth0_mac
fi
echo -e " MAC0: $eth0_mac\n "

## Get MAC1 via BMC's REST command ##	
printf "\n > Get BMC MAC1 addresses via busctl command."
eth1_mac=$(busctl get-property xyz.openbmc_project.Network /xyz/openbmc_project/network/eth1 xyz.openbmc_project.Network.MACAddress MACAddress |sed 's/^...//;s/.$//;s/\://;s/\://;s/\://;s/\://;s/\://')
if [ "${#eth1_mac}" -ne 12 ]; then
	eth1_mac=0$eth1_mac
fi
echo -e " MAC1: $eth1_mac\n "

## Get PN via BMC's REST command ##
printf "\n > Get PartNumber via busctl command."
pn=$(busctl get-property xyz.openbmc_project.Inventory.Manager /xyz/openbmc_project/inventory/system/chassis/motherboard xyz.openbmc_project.Inventory.Decorator.Asset PartNumber |sed 's/^...//;s/.$//')
echo -e " PartNumber: $pn\n "

## Get SN via BMC's REST command ##
printf "\n > Get SerialNumber via busctl command."
sn=$(busctl get-property xyz.openbmc_project.Inventory.Manager /xyz/openbmc_project/inventory/system/chassis/motherboard xyz.openbmc_project.Inventory.Decorator.Asset SerialNumber |sed 's/^...//;s/.$//')
echo -e " SerialNumber: $sn\n "

## Get PrettyName via BMC's REST command ##
printf "\n > Get Original PrettyName via busctl command."
ptn=$(busctl get-property xyz.openbmc_project.Inventory.Manager /xyz/openbmc_project/inventory/system/chassis/motherboard/bmc xyz.openbmc_project.Inventory.Item PrettyName |sed 's/^...//;s/.$//')
echo -e " Original PrettyName: $ptn\n "

	
### Write data(MAC0, MAC1, PN, SN) to Json files ###
echo -e " > Write data to XML files\n "
sed -i "s/mac0/$eth0_mac/g" /home/root/vpddata.json
sed -i "s/mac1/$eth1_mac/g" /home/root/vpddata.json
sed -i "s/pn/$pn/g" /home/root/vpddata.json
sed -i "s/sn/$sn/g" /home/root/vpddata.json
sed -i "s/ptn/SYSTEM PLANAR/g" /home/root/vpddata.json

### Flash new VPD format data to the binary of eeprom ###
echo -e " > Flash new VPD format data to the binary of eeprom\n ---------------------------------"
/usr/bin/env write-eeprom
echo -e " ---------------------------------"

### Write VPD binary to EEPROM ###
printf " > Write the binary to EEPROM..."
cat /home/root/eeprom > /sys/bus/i2c/devices/8-0050/eeprom

### Run command to reset BMC’s VPD service ###
printf "\n > Reset BMC’s VPD service...\n"
systemctl stop op-vpd-parser.service
echo -e "\n > Stop op-vpd-parser.service\n "
systemctl start op-vpd-parser.service
echo -e "\n > Start op-vpd-parser.service\n "
