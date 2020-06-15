 Description:
 
 This tool is used to flash new Mihawk's VPD format to eeprom binary file,
 and initial update Mihawk's VPD format to eeprom(/sys/bus/i2c/devices/8-0050/eeprom) via updatevpd.sh.
 
 The things to be executed by script of updatevpd.sh :
 1. Check the data of eeprom whether is new. 
 (If not, continue with the following steps.)
 2. Update new VPD format to eeprom.
 3. Get the fru data via "busctl" (PartNumber, SerialNumber, MAC0 & MAC1).
 4. Use this CLI tool to update VPD data to eeprom.
 
 updatevpd.sh is enabled by write-eeprom.service.
 Because updatevpd.sh needs to use the busctl command to obtain data from the inventory, 
 the ideal execution time of write-eeprom.service is after the host state is started.
 
 ---------------------------------------------------------
 
 The using method of this CLI tool:
 
 Options:
  -h,--help                   Print this help message and exit
  -v,--value TEXT             Enter the data
  -a,--VINI_DR Needs: --value Update the value of VINI_DR_PrettyName. {writeEE -a -v 'VINI_DR_PrettyName'}ex. writeEE -a -v 'SYSTEM PLANAR'
  -b,--VINI_B1 Needs: --value Update the value of MAC0. {writeEE -b -v 'MAC0'}ex. writeEE -b -v '0894ef80a13d'
  -c,--OPFR_VD Needs: --value Update the value of OPFR_VD. {writeEE -c -v 'OPFR_VD'}ex. writeEE -c -v '03'
  -d,--OPFR_VN Needs: --value Update the value of OPFR_VN. {writeEE -d -v 'OPFR_VN'}ex. writeEE -d -v 'IBM'
  -e,--OPFR_DR Needs: --value Update the value of OPFR_DR_PrettyName. {writeEE -e -v 'OPFR_DR_PrettyName'}ex. writeEE -e -v 'SYSTEM PLANAR'
  -f,--OPFR_VP Needs: --value Update the value of OPFR_VP_PartNumber. {writeEE -f -v 'OPFR_VP_PartNumber'}ex. writeEE -f -v '55504P01D006'
  -g,--OPFR_VS Needs: --value Update the value of OPFR_VS_SerialNumber. {writeEE -g -v 'OPFR_VS_SerialNumber'}ex. writeEE -g -v '92200001J0SA'
  -j,--OPFR_MB Needs: --value Update the value of OPFR_MB. {writeEE -j -v 'OPFR_MB'}ex. writeEE -j -v '0100000000000000'
  -k,--OPFR_B1 Needs: --value Update the value of MAC1. {writeEE -k -v MAC1}ex. writeEE -k -v '0894ef80a13e'
 

              
 Author:   Andy YF Wang (Andy_YF_Wang@wistron.com)                                  
 Date  :   2020/06/14                                                               
 Ver.  :   1.0.0                                                                    

