#ifndef __WRITEEE_H_
#define __WRITEEE_H_

#define pName_addr_0 0x74
#define pName_addr_1 0xbc
#define pNumber_addr 0xcf
#define sNumber_addr 0xe2
#define mac0_addr 0x87
#define mac1_addr 0x100

using namespace std; 

int fd;                                    // eeprom binary file.
void openBinFile();                        // Open the binary file of eeprom.
void rwPrettyName(int addr);               // Write & read "PrettyName" to the binary file of eeprom.
void rwPartNumber(int addr);               // Write & read "PartNumber" to the binary file of eeprom.
void rwSerialNumber(int addr);             // Write & read "SerialNumber" to the binary file of eeprom.
void rwMAC(int addr, string data);         // Write & read "MAC0" to the binary file of eeprom.
string hexToASCII(string hex);             // Hex-to-ASCII for string.
void paserXML();                           // Paser the xml file.


string vpdMAC0;       // The VPD_Date of MAC0.
string vpdMAC1;       // The VPD_Date of MAC1.
string vpdPN;         // The VPD_Date of PartNumber.
string vpdSN;         // The VPD_Date of SerialNumber.
string vpdPTN;        // The VPD_Date of PrettyName.


#endif
