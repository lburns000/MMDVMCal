#if !defined(JSONFILE_H)
#define	JSONFILE_H

#include <nlohmann/json.hpp>
#include <fstream>

/**Manages I/O between a JSON file on disk and JSON data in the program. File data is in the 
   following format:

    {
        "offset": {
            "vhfTx": 0,
            "vhfRx": 0,
            "uhfTx": 0,
            "uhfRx": 0
        }
    }
*/
class CJSONFile
{
public:
    /**Open the specified file. Open in write mode if createNew is true, otherwise open in 
       read mode. If file was opened and subsequently read successfully, this file is valid.*/
    CJSONFile(const std::string& filename, bool createNew = false);

    /**Before destruction, close the file if it is open.*/
    ~CJSONFile();

    /**Don't allow copying*/
    CJSONFile(const CJSONFile&) = delete;
    CJSONFile& operator=(const CJSONFile&) = delete;

    /**Update the given JSON data with data read from the file. Return false if there was an 
       error, otherwise return true.*/
    bool read();

    /**Write the given JSON data to the file. Return false if there was an error, otherwise 
       return true.*/
    bool write();

    /**Return true if the file is open and in a valid state. Return false otherwise.*/
    bool isValid() const { return m_valid; };

    /**Write an offset integer value to internal data.*/
    bool setOffsetValue(const std::string& key, int value);

    /**Read an offset integer value from internal data. Return 0 if read failed.*/
    int getOffsetValue(const std::string& key);

    /**Get the JSON string in raw compressed format.*/
    std::string getPlainString();

    /**Get the JSON string in human-readable format.*/
    std::string getFormattedString();

private:
    /**If overwrite is true, open the file in write mode, otherwise open in read-only
       mode.*/
    bool open(bool overwrite = false);

    /**Close the file if it is open.*/
    void close();

    /**Check that offset data exists and is of the correct type. Return accordingly.*/
    bool checkData();

    /**Set the value of a specific key within the specified section, creating it if it doesn't exist.*/
    template<class S, class K, class V>
    void setValue(const S& section, const K& key, const V& value);

    /**Get the value of a specific key within the specified section. */
    template <class S, class K, class V>
    V getValue(const S& section, const K& key);

    std::string    m_filename;
    std::fstream   m_file;
    nlohmann::json m_data;
    bool           m_valid;
};

template <class S, class K, class V>
inline void CJSONFile::setValue(const S &section, const K &key, const V &value)
{
    m_data[section][key] = value;
}

template <class S, class K, class V>
inline V CJSONFile::getValue(const S& section, const K& key)
{
    return m_data[section][key];
}


#endif