/*
 * ebu2srt - Subtitle converter from EBU-TT-D XML to SRT
 * 
 * SrtParser.h
 * 
 * Copyright 2018 Yann Muller
 * 
 * This program is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or any later version. (http://www.gnu.org/licenses/)
 */

#ifndef SRC_SRTPARSER_H_
#define SRC_SRTPARSER_H_

#include "EbuReader.h"
#include "SrtWriter.h"
#include <tinyxml2.h>
#include <string>

using namespace std;
using namespace tinyxml2;

/**
 * @class SrtParser
 * @file SrtParser.h
 * @brief A class that takes XML input from the Reader and sends processed subtitles to the Writer.
 */
class SrtParser
{
public:
	/**
	 * @brief   Class constructor takes a Reader and Writer as mandatory parameters
	 *
	 * The given input file is open and if in the correct EBU XML format is parsed.
     * The first element is located and the timing offset is checked.
	 *
	 * @param [in] ebureader  the Reader class 
	 * @param [in] srtwriter  the Writer class 
	 */
    SrtParser( EbuReader* ebureader, SrtWriter* srtwriter );
    virtual ~SrtParser() {};

    /**
     * @brief starts the parsing of the subtitles
     */
    bool parseSubtitles();
    
    /**
     * @brief enables or disables the removal of SDH annotations
     * 
     * This method turns on or off the removal of Subtitles for the Deaf or 
     * Hard-of-hearing (SDH). This feature is experimental and might have some 
     * unexpected results. (There is no agreed format for SDH)
     */
    void setSDHCleaning( bool clean );

private:

    /**
     * @brief converts the timestamp to SRT format
     */
    bool convertTime( string& time );
    /**
     * @brief attempts to remove SDH annotations
     */
    bool removeSDHText( string& subtitle );
    
    EbuReader* mEbuReader;
    SrtWriter* mSrtWriter;
    
    bool mCleanSDH;

};

#endif /* SRC_SRTPARSER_H_ */
