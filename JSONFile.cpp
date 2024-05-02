#include "JSONFile.h"

CJSONFile::CJSONFile(const std::string &filename, CJSONData *jsonData) :
m_filename(filename),
m_file(nullptr),
m_jsonData(jsonData),
m_valid(false)
{
    if (jsonData == nullptr) {
        return;
    }

    if (!open()) {
        return;
    }

    // if (!read()) {
    //     m_file.close();
    //     return;
    // }
}

CJSONFile::~CJSONFile()
{
    close();
    if (m_file != nullptr) {
        delete m_file;
    }
}

bool CJSONFile::read()
{
    if (!m_file->is_open()) {
        ::fprintf(stdout, "CJSONFile::read(): File is not open. Returning false.\n");
        return false;
    }

    ::fprintf(stdout, "CJSONFile::read(): Setting JSON data...\n");
    m_jsonData->setData(m_file);


    m_valid = true;
    return true;
}

bool CJSONFile::write()
{
    if (!m_file->is_open()) {
        return false;
    }

    m_jsonData->getData(m_file);

    return true;
}

bool CJSONFile::open()
{
    //::fprintf(stdout, "Attempting to open EEPROM.json.\n");
    m_file = new std::fstream;
    m_file->open(m_filename, std::ios::in | std::ios::out);
    if (m_file->is_open()) {
        //::fprintf(stdout, "EEPROM.json opened successfully! Getting the data from it...\n");
        m_jsonData->setData(m_file);
        return true;
    }

    ::fprintf(stdout, "EEPROM.json did not open, attempting to create file...\n");

    // Create the file if it doesn't exist
    std::fstream newFile;
    newFile.open(m_filename, std::ios::out | std::ios::trunc);
    if (!newFile.is_open()) {
        ::fprintf(stderr, "Error creating EEPROM.json.\n");
        return false;
    }

    ::fprintf(stdout, "EEPROM.json successfully created. Setting JSON data to default values...\n");
    m_jsonData->setValue("Offset", "VhfTx", 0);
    m_jsonData->setValue("Offset", "VhfRx", 0);
    m_jsonData->setValue("Offset", "UhfTx", 0);
    m_jsonData->setValue("Offset", "UhfRx", 0);

    ::fprintf(stdout, "Writing JSON data to file...\n");
    m_jsonData->getData(&newFile);

    // Reopen the file in r/w mode
    newFile.close();

    ::fprintf(stdout, "Reopening EEPROM.json in r/w mode...\n");
    m_file->open(m_filename, std::ios::in | std::ios::out);
    if (!m_file->is_open()) {
        ::fprintf(stdout, "Error reopening EEPROM.json.\n");
        return false;
    }

    return true;
}

void CJSONFile::close()
{
    if (m_file->is_open()) {
        m_file->close();
    }
}
