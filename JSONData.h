/*
    {
        "offset": {
            "vhfTx": "0",
            "vhfRx": "0",
            "uhfTx": "0",
            "uhfRx": "0"
        }
    }

 */

#if !defined(JSONDATA_H)
#define	JSONDATA_H

#include <nlohmann/json.hpp>
#include <fstream>

class CJSONData
{
public:
    CJSONData();
    ~CJSONData();

    /**Set the value of a specific key within the specified section, creating it if it doesn't exist.*/
    template<class S, class K, class V>
    void setValue(const S& section, const K& key, const V& value);

    template <class S, class K, class V>
    V getValue(const S& section, const K& key);

    /**Set the value of the whole data from a file.*/
    void setData(std::fstream* file);

    /**Get the value of the whole data and store in a file.*/
    void getData(std::fstream* file);

    //void addValue(const std::string& section, const std::string& key, const std::string& value);

    /**Get the JSON data in raw format, suitable for parsing.*/
    std::string getPlainString();

    /**Get the JSON data in a human-friendly format.*/
    std::string getFormattedString();

    /**Check if the data is valid.*/
    bool isValid() { return m_valid; }

private:
    bool checkData();

    nlohmann::json m_data;
    bool           m_valid;
};

template <class S, class K, class V>
inline void CJSONData::setValue(const S &section, const K &key, const V &value)
{
    m_data[section][key] = value;
}

template <class S, class K, class V>
inline V CJSONData::getValue(const S& section, const K& key)
{
    return m_data[section][key];
}

#endif