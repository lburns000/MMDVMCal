#if !defined(JSONDATA_H)
#define	JSONDATA_H

#include "JSONFile.h"
#include <string>

/**Handle the high-level data stored in JSON file.*/
class CJSONData
{
public:
    CJSONData();
    ~CJSONData();

    /**Open specified file and read JSON data in it.*/
    void getDataFromFile(const std::string& filename);

    /**Open specified file creating it if it doesn't exist and reset all data in it 
       to default values.*/
    bool initializeFile(const std::string& filename);

    /**Return VHF Rx offset value*/
	int getRxOffsetVHF();

    /**Return VHF Tx offset value*/
	int getTxOffsetVHF();

    /**Return UHF Rx offset value*/
	int getRxOffsetUHF();

    /**Return UHF Tx offset value*/
	int getTxOffsetUHF();

    /**Set VHF Rx offset value*/
	void setRxOffsetVHF(int offset);

    /**Set VHF Tx offset value*/
	void setTxOffsetVHF(int offset);

    /**Set UHF Rx offset value*/
	void setRxOffsetUHF(int offset);

    /**Set UHF Tx offset value*/
	void setTxOffsetUHF(int offset);

    /**If data is not valid, return false. Otherwise, store locally stored offset data into given 
       integer references and return true.*/
	bool readOffsetData(int &rxVHF, int &txVHF, int &rxUHF, int &txUHF);

    /**Write locally stored offset data into JSON file*/
	bool writeOffsetData();

    // /**Get the JSON data in raw format, suitable for parsing.*/
    // std::string getPlainString();

    // /**Get the JSON data in a human-friendly format.*/
    // std::string getFormattedString();

    /**Check if the data is valid.*/
    bool isValid() { return m_valid; }

private:
    /**Return true if file is open and its data is valid. Otherwise return false.*/
    bool checkData();

    /**Set all offset values to zero.*/
    void initializeOffsetValues();

    /**Open the specified JSON file. If createNew is true, create the file if it doesn't exist. 
       Return true if successful and file data is valid, otherwise, return false.*/
    bool openFile(const std::string& filename, bool createNew = false);

    bool           m_valid;
    CJSONFile*     m_file;
    int            m_txOffsetUHF;
    int            m_rxOffsetUHF;
    int            m_txOffsetVHF;
    int            m_rxOffsetVHF;
};

#endif