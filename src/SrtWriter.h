/*
 * ebu2srt - Subtitle converter from EBU-TT-D XML to SRT
 * 
 * SrtWriter.h
 * 
 * Copyright 2018 Yann Muller
 * 
 * This program is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or any later version. (http://www.gnu.org/licenses/)
 */

#ifndef SRC_SRTWRITER_H_
#define SRC_SRTWRITER_H_

#include <string>
#include <fstream>

using namespace std;

/**
 * @class SrtWriter
 * @file SrtWriter.h
 * @brief This class writes SRT subtitles to file.
 */
class SrtWriter
{
public:
    SrtWriter();
    virtual ~SrtWriter() {};
    
	/**
	 * @brief   opens the given SRT subtitle file for writing
	 *
	 * The given output file is opened.
	 *
	 * @param [in] filename  the SRT file to write to
	 *
	 * @retval true   The file was opened successfully.
	 * @retval false  Failed to open the file.
	 */
    bool openOutputFile( const string& filename );
    
	/**
	 * @brief   closes the output file
	 *
	 * The output file is closed.
	 */
    void closeOutputFile();
    
	/**
	 * @brief   writes the provided subtitle to file
	 *
	 * The given subtitle is written to the output file. Make sure to call
     * openOutputFile() first.
	 *
	 * @param [in] begin  the start time of the subtitle
	 * @param [in] end  the end time of the subtitle
	 * @param [in] text  the text of the subtitle
	 *
	 * @retval true   The subtitle was written to file successfully.
	 * @retval false  Failed to write the subtitle.
	 */
    bool writeSubtitle( const string& begin, const string& end, const string& text );

private:
    // the output file as a stream
    ofstream mOutput;
    
    // index of the current subtitle
    int mStNumber;
    
};

#endif /* SRC_SRTWRITER_H_ */
