/*
 * ebu2srt - Subtitle converter from EBU-TT-D XML to SRT
 * 
 * SrtWriter.cpp
 * 
 * Copyright 2018 Yann Muller
 * 
 * This program is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or any later version. (http://www.gnu.org/licenses/)
 */

#include "SrtWriter.h"
#include "Print.h"
#include <string>
#include <fstream>

using namespace std;

SrtWriter::SrtWriter() :
    mStNumber(0)
{
}

bool SrtWriter::openOutputFile(const string& filename)
{
    DEBUG("Opening " << filename );
    mOutput.open( filename );
    if( !mOutput.is_open() )
    {
        DEBUG("Failed to open output file.");
        return false;
    }
    return true;
}

void SrtWriter::closeOutputFile()
{
    mOutput.close();
    PRINT( "Processed " << mStNumber << " subtitles." );
}

bool SrtWriter::writeSubtitle(const string& begin, const string& end, const string& text)
{
    // SRT subtitles are in the format:
    // Subtitle index
    // HH:MM::SS,mmm --> HH:MM:SS,mmm
    // Subtitle text
    // More subtitle text
    // [blank line separator]
    
    if( !mOutput.is_open() )
    {
        ERROR("Please open the output file before attempting to write to it.");
        return false;
    }
    
    if( !text.empty() )
    {
        mStNumber++;
        mOutput << mStNumber << endl;
        mOutput << begin << " --> " << end << endl;
        mOutput << text << endl << endl; // ends with a blank line
    
    }
    return true;
}


