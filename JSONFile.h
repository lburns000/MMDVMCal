/* Manages the I/O between JSON data and filesystem. Contains 
   a pointer to the JSON data that is modified outside this 
   class. */

#if !defined(JSONFILE_H)
#define	JSONFILE_H

#include "JSONData.h"
#include <fstream>

class CJSONFile
{
public:
/**Attempt to open the specified file in r/w text mode. If 
   there was an error, set m_valid as false. Otherwise, set 
   it to true.*/
    CJSONFile(const std::string& filename, CJSONData* jsonData);

/**Close the file if it is open.*/
    ~CJSONFile();

/**Update the JSON data with data read from the file. Return
   false if there was an error, otherwise return true.*/
    bool read();

/**Write the current JSON data to the file. Return false if 
   there was an error, otherwise return true.*/
    bool write();

private:
    bool open();
    void close();

    std::string   m_filename;
    std::fstream* m_file;
    CJSONData*    m_jsonData;
    bool          m_valid;
};
#endif