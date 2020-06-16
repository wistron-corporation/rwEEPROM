#pragma once
#include <fstream>

using namespace std;

/**
 * The parameter which is used by fstream().
 * - the file of eeprom.
 */
fstream efile;

/**
 * The parameter which is used by CLI.
 * - the VPD data.
 */
string value;

/**
 * The parameter which is used by parseJsonFromFile().
 * - the path of eeprom.
 */
string eepromPATH;

/**
 * Five kinds of VPD data, used by getDataAddr()
 * to get addr of VPD data.
 */
enum class vpdData : int
{
    VINI_DR,
    VINI_B1,
    OPFR_VD,
    OPFR_VN,
    OPFR_DR,
    OPFR_VP,
    OPFR_VS,
    OPFR_MB,
    OPFR_B1
};

/**
 * Init all data in Mihawk's eeprom if the VPD format is old.
 */
void initData();

/**
 * Do the action of "writing data" to the binary file of eeprom.
 * @param[in] keyword - the keyword of VPD_Data.
 * @param[in] data - the data which will be written in eeprom.
 */
void writeData(int keyword, string data);

/**
 * Write "VD" to the binary file of eeprom.
 * @param[in] data - the data which will be written in eeprom.
 */
void rwVD(string data);

/**
 * Write "VN" to the binary file of eeprom, ex.IBM.
 * @param[in] data - the data which will be written in eeprom.
 */
void rwVN(string data);

/**
 * Write "MB" to the binary file of eeprom.
 * @param[in] data - the data which will be written in eeprom.
 */
void rwMB(string data);

/**
 * Write "PrettyName" to the binary file of eeprom.
 * @param[in] addr - the address which will be written in eeprom.
 * @param[in] data - the data which will be written in eeprom.
 */
void rwPrettyName(int addr, string data);

/**
 * Write "PartNumber" to the binary file of eeprom.
 * @param[in] data - the data which will be written in eeprom.
 */
void rwPartNumber(string data);

/**
 * Write "SerialNumber" to the binary file of eeprom.
 * @param[in] data - the data which will be written in eeprom.
 */
void rwSerialNumber(string data);

/**
 * Write "MAC" to the binary file of eeprom.
 * @param[in] addr - the address which will be written in eeprom.
 * @param[in] data - the data which will be written in eeprom.
 */
void rwMAC(int addr, string data);

/**
 * Transfer the hex to ASCII.
 * @param[in] hex - the hex which will be transfered to the ASCII.
 * @return string - the ASCII data.
 */
string hexToASCII(string hex);

/**
 * Paser the json file.
 * @param[in] filename - the Json file.
 */
void parseJsonFromFile(const char* filename);