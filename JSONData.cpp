#include "JSONData.h"
#include <sstream>
#include <iostream>

CJSONData::CJSONData() :
m_data(),
m_valid(false)
{
}

CJSONData::~CJSONData()
{
}

// void CJSONData::addValue(const std::string &section, const std::string &key, const std::string &value)
// {
//     assert(section.size() > 0);
//     assert(key.size() > 0);
//     assert(value.size() > 0);

//     m_data[section][key] = value;
// }

void CJSONData::setData(std::fstream* file)
{
    *file >> m_data;
    m_valid = checkData();
    //std::cout << "CJSONData::setData(): Printing data from file: ";
    //std::cout << m_data << std::endl;
}

void CJSONData::getData(std::fstream* file)
{
    *file << m_data.dump(4) << std::flush;
}

std::string CJSONData::getPlainString()
{
    return m_data.dump();
}

std::string CJSONData::getFormattedString()
{
    return m_data.dump(4);
}

bool CJSONData::checkData()
{
    try
    {
        int uhfTx = getValue<std::string, std::string, int>("Offset", "UhfTx");
        
        if (!m_data["Offset"]["UhfTx"].is_number_integer())
            return false;
    }
    catch (std::exception &e)
    {
        ::fprintf(stdout, "Error reading UHF Tx offset: %s\n", e.what());
        return false;
    }

    try
    {
        int uhfRx = getValue<std::string, std::string, int>("Offset", "UhfRx");

        if (!m_data["Offset"]["UhfRx"].is_number_integer())
            return false;
    }
    catch (std::exception &e)
    {
        ::fprintf(stdout, "Error reading UHF Rx offset: %s\n", e.what());
        return false;
    }

    try
    {
        int vhfTx = getValue<std::string, std::string, int>("Offset", "VhfTx");

        if (!m_data["Offset"]["VhfTx"].is_number_integer())
            return false;
    }
    catch (std::exception &e)
    {
        ::fprintf(stdout, "Error reading VHF Tx offset: %s\n", e.what());
        return false;
    }

    try
    {
        int vhfRx = getValue<std::string, std::string, int>("Offset", "VhfRx");

        if (!m_data["Offset"]["VhfRx"].is_number_integer())
            return false;
    }
    catch (std::exception &e)
    {
        ::fprintf(stdout, "Error reading VHF Rx offset: %s\n", e.what());
        return false;
    }

    return true;
}
