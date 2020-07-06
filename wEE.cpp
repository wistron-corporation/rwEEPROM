#include "wEE.hpp"

#include "init_eeprom.hpp"

#include <bits/stdc++.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>

#include <algorithm>
#include <iostream>
#include <string>

static const auto EEPROM_JSON = "/usr/share/write-eeprom/wEE.json";

using json = nlohmann::json;
using namespace CLI;

int main(int argc, char** argv)
{
    int rc = 0;

    // Parse the json file.
    parseJsonFromFile(EEPROM_JSON);

    initData();

    App app{"VPD Command line tool to update VPD data in eeprom."};

    auto val = app.add_option("--value, -v", value, "Enter the data");

    auto wVINIDR_Flag =
        app.add_flag("--VINI_DR, -a", "Update the value of VINI_DR_PrettyName. "
                                      "{writeEE -a -v 'VINI_DR_PrettyName'}"
                                      "ex. writeEE -a -v 'SYSTEM PLANAR'")
            ->needs(val);

    auto wVINIB1_Flag =
        app.add_flag("--VINI_B1, -b",
                     "Update the value of MAC0. {writeEE -b -v 'MAC0'}"
                     "ex. writeEE -b -v '0894ef80a13d'")
            ->needs(val);

    auto wOPFRVD_Flag =
        app.add_flag("--OPFR_VD, -c",
                     "Update the value of OPFR_VD. {writeEE -c -v 'OPFR_VD'}"
                     "ex. writeEE -c -v '03' ")
            ->needs(val);

    auto wOPFRVN_Flag =
        app.add_flag("--OPFR_VN, -d",
                     "Update the value of OPFR_VN. {writeEE -d -v 'OPFR_VN'}"
                     "ex. writeEE -d -v 'IBM'")
            ->needs(val);

    auto wOPFRDR_Flag =
        app.add_flag("--OPFR_DR, -e", "Update the value of OPFR_DR_PrettyName. "
                                      "{writeEE -e -v 'OPFR_DR_PrettyName'}"
                                      "ex. writeEE -e -v 'SYSTEM PLANAR'")
            ->needs(val);

    auto wOPFRVP_Flag =
        app.add_flag("--OPFR_VP, -f", "Update the value of OPFR_VP_PartNumber. "
                                      "{writeEE -f -v 'OPFR_VP_PartNumber'}"
                                      "ex. writeEE -f -v '55504P01D006'")
            ->needs(val);

    auto wOPFRVS_Flag =
        app.add_flag("--OPFR_VS, -g",
                     "Update the value of OPFR_VS_SerialNumber. {writeEE -g -v "
                     "'OPFR_VS_SerialNumber'}"
                     "ex. writeEE -g -v '92200001J0SA'")
            ->needs(val);

    auto wOPFRMB_Flag =
        app.add_flag("--OPFR_MB, -j",
                     "Update the value of OPFR_MB. {writeEE -j -v 'OPFR_MB'}"
                     "ex. writeEE -j -v '0100000000000000'")
            ->needs(val);

    auto wOPFRB1_Flag =
        app.add_flag("--OPFR_B1, -k",
                     "Update the value of MAC1. {writeEE -k -v MAC1}"
                     "ex. writeEE -k -v '0894ef80a13e'")
            ->needs(val);

    CLI11_PARSE(app, argc, argv);

    if (efile)
    {
        try
        {
            if (*wVINIDR_Flag)
            {
                writeData(static_cast<int>(vpdData::VINI_DR), value);
            }
            else if (*wVINIB1_Flag)
            {
                writeData(static_cast<int>(vpdData::VINI_B1), value);
            }
            else if (*wOPFRVD_Flag)
            {
                writeData(static_cast<int>(vpdData::OPFR_VD), value);
            }
            else if (*wOPFRVN_Flag)
            {
                writeData(static_cast<int>(vpdData::OPFR_VN), value);
            }
            else if (*wOPFRDR_Flag)
            {
                writeData(static_cast<int>(vpdData::OPFR_DR), value);
            }
            else if (*wOPFRVP_Flag)
            {
                writeData(static_cast<int>(vpdData::OPFR_VP), value);
            }
            else if (*wOPFRVS_Flag)
            {
                writeData(static_cast<int>(vpdData::OPFR_VS), value);
            }
            else if (*wOPFRMB_Flag)
            {
                writeData(static_cast<int>(vpdData::OPFR_MB), value);
            }
            else if (*wOPFRB1_Flag)
            {
                writeData(static_cast<int>(vpdData::OPFR_B1), value);
            }
        }
        catch (exception& e)
        {
            cerr << e.what();
        }
    }

    efile.close();

    return rc;
}

// Init all data in Mihawk's eeprom
// if the VPD format is old.
void initData()
{
    int i;
    char check[3];

    efile.open(const_cast<char*>(eepromPATH.c_str()),
               ios::in | ios::out | ios::binary);
    if (!efile)
    {
        std::cerr << "open the file of eeprom error!" << std::endl;
        efile.close();
    }

    // Check the eeprom data(mac addr) whether is old.
    // Init the eeprom if it is the old format.
    efile.seekg(162, ios::beg);
    efile.read(check, 2);
    if (check[0] == 'B' && check[1] == '1')
    {
        for (i = 0; i < 288; i++)
        {
            efile.seekp(i, ios::beg);
            efile.write(hexToASCII(initMihawkdata[i]).c_str(), 2);
        }
    }

    efile.close();
}

// Write data.
void writeData(int keyword, string data)
{
    if (!efile.is_open())
    {
        efile.open(const_cast<char*>(eepromPATH.c_str()),
                   ios::in | ios::out | ios::binary);
    }

    vpdData code;
    code = static_cast<vpdData>(keyword);
    switch (code)
    {
        case vpdData::VINI_DR:
        {
            rwPrettyName(116, data);
            break;
        }
        case vpdData::VINI_B1:
        {
            rwMAC(135, data);
            break;
        }
        case vpdData::OPFR_VD:
        {
            rwVD(data);
            break;
        }
        case vpdData::OPFR_VN:
        {
            rwVN(data);
            break;
        }
        case vpdData::OPFR_DR:
        {
            rwPrettyName(188, data);
            break;
        }
        case vpdData::OPFR_VP:
        {
            rwPartNumber(data);
            break;
        }
        case vpdData::OPFR_VS:
        {
            rwSerialNumber(data);
            break;
        }
        case vpdData::OPFR_MB:
        {
            rwMB(data);
            break;
        }
        case vpdData::OPFR_B1:
        {
            rwMAC(256, data);
            break;
        }
        default:
            break;
    }

    efile.close();
}

// Write the data of PrettyName.
void rwPrettyName(int addr, string data)
{
    char* bufw = const_cast<char*>(data.c_str());
    std::cout << "The data of PrettyName is : " << data.c_str() << std::endl;

    if (!efile.is_open())
    {
        efile.open(const_cast<char*>(eepromPATH.c_str()),
                   ios::in | ios::out | ios::binary);
    }

    // Write data.
    efile.seekp(addr, ios::beg);
    efile.write(bufw, 16);

    efile.close();
}

// Write the data of PartNumber.
void rwPartNumber(string data)
{
    char* bufw = const_cast<char*>(data.c_str());
    std::cout << "The data of PartNumber is : " << data.c_str() << std::endl;

    if (!efile.is_open())
    {
        efile.open(const_cast<char*>(eepromPATH.c_str()),
                   ios::in | ios::out | ios::binary);
    }

    efile.seekp(207, ios::beg);
    efile.write(bufw, 16);

    efile.close();
}

// Write the data of SerialNumber.
void rwSerialNumber(string data)
{
    char* bufw = const_cast<char*>(data.c_str());
    std::cout << "The data of SerialNumber is : " << data.c_str() << std::endl;

    if (!efile.is_open())
    {
        efile.open(const_cast<char*>(eepromPATH.c_str()),
                   ios::in | ios::out | ios::binary);
    }

    efile.seekp(226, ios::beg);
    efile.write(bufw, 16);

    efile.close();
}

// Write the data of MAC.
// Separate the string to six part
// and write them to eeprom separately.
void rwMAC(int addr, string data)
{
    std::cout << "The data of MAC is : " << data.c_str() << std::endl;

    // Separate the string to six parts for updating.
    string hvalue0 = data.substr(0, 2);
    string hvalue1 = data.substr(2, 2);
    string hvalue2 = data.substr(4, 2);
    string hvalue3 = data.substr(6, 2);
    string hvalue4 = data.substr(8, 2);
    string hvalue5 = data.substr(10, 2);

    char bufw0[3];
    char bufw1[3];
    char bufw2[3];
    char bufw3[3];
    char bufw4[3];
    char bufw5[3];

    strcpy(bufw0, hexToASCII(hvalue0).c_str());
    strcpy(bufw1, hexToASCII(hvalue1).c_str());
    strcpy(bufw2, hexToASCII(hvalue2).c_str());
    strcpy(bufw3, hexToASCII(hvalue3).c_str());
    strcpy(bufw4, hexToASCII(hvalue4).c_str());
    strcpy(bufw5, hexToASCII(hvalue5).c_str());

    if (!efile.is_open())
    {
        efile.open(const_cast<char*>(eepromPATH.c_str()),
                   ios::in | ios::out | ios::binary);
    }

    efile.seekp(addr, ios::beg);
    efile.write(bufw0, 2);

    efile.seekp(addr + 1, ios::beg);
    efile.write(bufw1, 2);

    efile.seekp(addr + 2, ios::beg);
    efile.write(bufw2, 2);

    efile.seekp(addr + 3, ios::beg);
    efile.write(bufw3, 2);

    efile.seekp(addr + 4, ios::beg);
    efile.write(bufw4, 2);

    efile.seekp(addr + 5, ios::beg);
    efile.write(bufw5, 2);

    efile.close();
}

// Write the data of VD.
void rwVD(string data)
{
    char* bufw = const_cast<char*>(data.c_str());
    std::cout << "The data of VD is : " << data.c_str() << std::endl;

    if (!efile.is_open())
    {
        efile.open(const_cast<char*>(eepromPATH.c_str()),
                   ios::in | ios::out | ios::binary);
    }

    // Write data.
    efile.seekp(164, ios::beg);
    efile.write(bufw, 2);

    efile.close();
}

// Write the data of VN.
void rwVN(string data)
{
    char* bufw = const_cast<char*>(data.c_str());
    std::cout << "The data of VD is : " << data.c_str() << std::endl;

    if (!efile.is_open())
    {
        efile.open(const_cast<char*>(eepromPATH.c_str()),
                   ios::in | ios::out | ios::binary);
    }

    // Write data.
    efile.seekp(169, ios::beg);
    efile.write(bufw, 16);

    efile.close();
}

// Write the data of MB.
void rwMB(string data)
{
    std::cout << "The data of MB is : " << data.c_str() << std::endl;

    // Separate the string to eight parts for updating.
    string hvalue0 = data.substr(0, 2);
    string hvalue1 = data.substr(2, 2);
    string hvalue2 = data.substr(4, 2);
    string hvalue3 = data.substr(6, 2);
    string hvalue4 = data.substr(8, 2);
    string hvalue5 = data.substr(10, 2);
    string hvalue6 = data.substr(12, 2);
    string hvalue7 = data.substr(14, 2);

    char bufw0[3];
    char bufw1[3];
    char bufw2[3];
    char bufw3[3];
    char bufw4[3];
    char bufw5[3];
    char bufw6[3];
    char bufw7[3];

    strcpy(bufw0, hexToASCII(hvalue0).c_str());
    strcpy(bufw1, hexToASCII(hvalue1).c_str());
    strcpy(bufw2, hexToASCII(hvalue2).c_str());
    strcpy(bufw3, hexToASCII(hvalue3).c_str());
    strcpy(bufw4, hexToASCII(hvalue4).c_str());
    strcpy(bufw5, hexToASCII(hvalue5).c_str());
    strcpy(bufw6, hexToASCII(hvalue6).c_str());
    strcpy(bufw7, hexToASCII(hvalue7).c_str());

    efile.seekp(245, ios::beg);
    efile.write(bufw0, 2);

    efile.seekp(246, ios::beg);
    efile.write(bufw1, 2);

    efile.seekp(247, ios::beg);
    efile.write(bufw2, 2);

    efile.seekp(248, ios::beg);
    efile.write(bufw3, 2);

    efile.seekp(249, ios::beg);
    efile.write(bufw4, 2);

    efile.seekp(250, ios::beg);
    efile.write(bufw5, 2);

    efile.seekp(251, ios::beg);
    efile.write(bufw6, 2);

    efile.seekp(252, ios::beg);
    efile.write(bufw7, 2);

    efile.close();
}

// Hex-to-ASCII
string hexToASCII(string hex)
{
    // Initialize the ASCII code string as empty.
    string ascii_value = "";
    for (size_t i = 0; i < hex.length(); i += 2)
    {
        // Extract two characters from hex string.
        string part_value = hex.substr(i, 2);

        // Change it into base 16 and typecast as the character.
        char ch = std::stoul(part_value, nullptr, 16);

        // Add this char to final ASCII string.
        ascii_value += ch;
    }
    return ascii_value;
}

// Parse the json file.
void parseJsonFromFile(const char* filename)
{
    ifstream jfile;
    jfile.open(filename);
    if (!jfile.is_open())
    {
        std::cerr << "Can't open json file." << std::endl;
    }

    auto jfdata = json::parse(jfile, nullptr, false);
    if (jfdata.is_discarded())
    {
        std::cerr << "Parser json file fail." << std::endl;
    }

    static const std::vector<json> empty{};
    std::vector<json> reading = jfdata.value("frus", empty);
    if (!reading.empty())
    {
        for (const auto& instance : reading)
        {
            eepromPATH = instance.value("PATH", "");
        }
    }
    else
    {
        std::cerr << "Can't get the VPDdata" << std::endl;
    }

    jfile.close();
}
