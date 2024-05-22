/*
 *   Copyright (C) 2018 by Andy Uribe CA6JAU
 *   Copyright (C) 2018 by Bryan Biedenkapp N2PLL
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#if !defined(BERCAL_H)
#define BERCAL_H

#include <string>
#include "Timer.h"

enum FEC_TEST_TYPE {
	FTT_DSTAR  = 0,
	FTT_DMR    = 1,
	FTT_YSF    = 2,
	FTT_P25    = 3,
	FTT_NXDN   = 4
};

class CBERCal {
public:
	CBERCal();
	~CBERCal();

	void doFEC(const unsigned char* buffer, const unsigned char m_tag, FEC_TEST_TYPE fecType, bool showOutput = true, float* BER = nullptr);

	void DSTARFEC(const unsigned char* buffer, const unsigned char m_tag, float* BER = nullptr);
	void DMRFEC(const unsigned char* buffer, const unsigned char m_seq, float* BER = nullptr);
	void DMR1K(const unsigned char *buffer, const unsigned char m_seq);
	void YSFFEC(const unsigned char* buffer, float* BER = nullptr);
	void P25FEC(const unsigned char* buffer, float* BER = nullptr);
	void NXDNFEC(const unsigned char* buffer, const unsigned char m_tag, float* BER = nullptr);

	float getCurrentBER();	// Get the current BER, even if the transmission isn't over

	void clock(unsigned int ms);

	static std::string FECTestTypeToString(FEC_TEST_TYPE type);

private:
	unsigned int m_errors;
	unsigned int m_bits;
	unsigned int m_frames;

	// These are used for storing the last run, so if the user stops transmitting, getCurrentBER() won't return 0
	unsigned int m_errorsPrev;
	unsigned int m_bitsPrev;
	unsigned int m_framesPrev;
	CTimer		 m_timer;
	bool         m_consoleOutputEnabled;

	void NXDNScrambler(unsigned char* data);
	unsigned int regenerateDStar(unsigned int& a, unsigned int& b);
	unsigned int regenerateDMR(unsigned int& a, unsigned int& b, unsigned int& c);
	unsigned int regenerateIMBE(const unsigned char* bytes);
	unsigned int regenerateYSFDN(unsigned char* bytes);

	unsigned char countErrs(unsigned char a, unsigned char b);
};

#endif
