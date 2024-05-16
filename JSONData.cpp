#include "JSONData.h"
#include <sstream>
#include <iostream>

CJSONData::CJSONData() :
m_valid(false),
m_file(nullptr),
m_txOffsetUHF(0),
m_rxOffsetUHF(0),
m_txOffsetVHF(0),
m_rxOffsetVHF(0)
{
}

CJSONData::~CJSONData()
{
    if (m_file != nullptr) {
        delete m_file;
    }
}

void CJSONData::getDataFromFile(const std::string &filename)
{
    if (!openFile(filename))
        return;

    m_txOffsetUHF = m_file->getOffsetValue("UhfTx");
    m_rxOffsetUHF = m_file->getOffsetValue("UhfRx");
    m_txOffsetVHF = m_file->getOffsetValue("VhfTx");
    m_rxOffsetVHF = m_file->getOffsetValue("VhfRx");

    m_valid = true;
}

bool CJSONData::initializeFile(const std::string &filename)
{
    initializeOffsetValues();

    if (!openFile(filename, true))
        return false;

    return writeOffsetData();
}

int CJSONData::getRxOffsetVHF()
{
    return m_rxOffsetVHF;
}

int CJSONData::getTxOffsetVHF()
{
    return m_txOffsetVHF;
}

int CJSONData::getRxOffsetUHF()
{
    return m_rxOffsetUHF;
}

int CJSONData::getTxOffsetUHF()
{
    return m_txOffsetUHF;
}

void CJSONData::setRxOffsetVHF(int offset)
{
    m_rxOffsetVHF = offset;
}

void CJSONData::setTxOffsetVHF(int offset)
{
    m_txOffsetVHF = offset;
}

void CJSONData::setRxOffsetUHF(int offset)
{
    m_rxOffsetUHF = offset;
}

void CJSONData::setTxOffsetUHF(int offset)
{
    m_txOffsetUHF = offset;
}

bool CJSONData::readOffsetData(int &rxVHF, int &txVHF, int &rxUHF, int &txUHF)
{
    if (!m_valid)
        return false;

    rxVHF = m_rxOffsetVHF;
    txVHF = m_txOffsetVHF;
    rxUHF = m_rxOffsetUHF;
    txUHF = m_txOffsetUHF;

    return true;
}

// std::string CJSONData::getPlainString()
// {
//     return m_file->getPlainString();
// }

// std::string CJSONData::getFormattedString()
// {
//     return m_file->getFormattedString();
// }

bool CJSONData::writeOffsetData()
{
    if (m_file == nullptr)
        return false;
    
    m_file->setOffsetValue("UhfTx", m_txOffsetUHF);
    m_file->setOffsetValue("UhfRx", m_rxOffsetUHF);
    m_file->setOffsetValue("VhfTx", m_txOffsetVHF);
    m_file->setOffsetValue("VhfRx", m_rxOffsetVHF);

    return m_file->write();
}

bool CJSONData::checkData()
{
    if (m_file == nullptr)
        return false;

    return m_file->isValid();
}

void CJSONData::initializeOffsetValues()
{
    m_rxOffsetUHF = 0;
    m_txOffsetUHF = 0;
    m_rxOffsetVHF = 0;
    m_txOffsetVHF = 0;
}

bool CJSONData::openFile(const std::string &filename, bool createNew)
{
    // Be sure we're working with a new file
    if (m_file != nullptr)
        delete m_file;

    // Open a new file
    m_file = new CJSONFile(filename, createNew);

    if (!createNew && !m_file->isValid()) {
        m_valid = false;
        return false;
    }

    return true;
}
