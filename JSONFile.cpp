#include "JSONFile.h"

CJSONFile::CJSONFile(const std::string &filename, bool createNew) :
m_filename(filename),
m_file(),
m_data(),
m_valid(false)
{
    // Attempt to open the file
    if (!open(createNew))
        return;

    // Don't read the file if there's no data in it
    if (createNew)
        return;

    // Read the file
    if (!read())
        return;

    m_valid = true;
}

CJSONFile::~CJSONFile()
{
    close();
}

bool CJSONFile::read()
{
    if (!m_file.is_open()) {
        ::fprintf(stdout, "CJSONFile::read(): File is not open. Returning false.\n");
        return false;
    }

    close();
    
    if (!open(false))
        return false;

    // ::fprintf(stdout, "CJSONFile::read(): Setting JSON data...\n");
    try {
        m_file >> m_data;
    }
    catch (...) {
        ::fprintf(stderr, "CJSONFile::read(): Error reading data from file.\n");
        return false;
    }

    return checkData();
}

bool CJSONFile::write()
{
    // If not creating a new file, it should be open already
    if (!m_file.is_open()) {
        return false;
    }

    // Close the file and reopen it in overwrite mode
    if (m_file.is_open())
        m_file.close();
    
    if (!open(true))
        return false;

    m_file << m_data.dump(4) << std::flush;
    // m_file << m_data; // << std::flush;

    return true;
}

bool CJSONFile::setOffsetValue(const std::string& key, int value)
{
    if ((key == "UhfTx") || (key == "UhfRx") || (key == "VhfTx") || (key == "VhfRx")) {
        setValue<const std::string&, const std::string&, int>("Offset", key, value);
        return true;
    }
    
    return false;
}

int CJSONFile::getOffsetValue(const std::string &key)
{
    if ((key == "UhfTx") || (key == "UhfRx") || (key == "VhfTx") || (key == "VhfRx")) {
        int offset = getValue<const std::string&, const std::string&, int>("Offset", key);
        return offset;
    }

    return 0;
}

std::string CJSONFile::getPlainString()
{
    return m_data.dump();
}

std::string CJSONFile::getFormattedString()
{
    return m_data.dump(4);
}

bool CJSONFile::open(bool overwrite)
{
    //::fprintf(stdout, "Attempting to open EEPROM.json.\n");
    if (overwrite)
        m_file.open(m_filename, std::ios::out | std::ios::trunc);
    else
        m_file.open(m_filename, std::ios::in);

    if (!m_file.is_open()) {
        return false;
    }

    return true;
}

void CJSONFile::close()
{
    if (m_file.is_open())
        m_file.close();

    m_data.clear();
}

bool CJSONFile::checkData()
{
    try
    {
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
