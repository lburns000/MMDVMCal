#include "JSONData.h"
#include <sstream>
#include <iostream>

CJSONData::CJSONData() :
m_data()
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
    //std::cout << "CJSONData::setData(): Printing data from file: ";
    //std::cout << m_data << std::endl;
}

void CJSONData::getData(std::fstream* file)
{
    *file << m_data << std::flush;
}

std::string CJSONData::getPlainString()
{
    return m_data.dump();
}

std::string CJSONData::getFormattedString()
{
    return m_data.dump(4);
}