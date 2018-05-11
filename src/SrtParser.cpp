/*
 * ebu2srt - Subtitle converter from EBU-TT-D XML to SRT
 * 
 * SrtParser.cpp
 * 
 * Copyright 2018 Yann Muller
 * 
 * This program is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or any later version. (http://www.gnu.org/licenses/)
 */

#include "SrtParser.h" 
#include "Print.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;
using namespace tinyxml2;

SrtParser::SrtParser(EbuReader* ebureader, SrtWriter* srtwriter) :
    mEbuReader(ebureader) , mSrtWriter(srtwriter), mCleanSDH(false)
{
}

void SrtParser::setSDHCleaning(bool clean)
{
    mCleanSDH = clean;
}

bool SrtParser::parseSubtitles()
{
    XMLElement* element = mEbuReader->nextSubtitle();

    while( element != nullptr )
    {
        string begin( element->Attribute( "begin" ) );
        string end( element->Attribute( "end" ) );
        convertTime( begin );
        convertTime( end );
        
        stringstream subtitlestream;
        
        // The subtitle text is usually in span elements but check if there is text here
        const char* text = element->GetText();
        if( text != nullptr )
        {
            subtitlestream << text;
        }

        for (XMLElement* child = element->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
        {
            // Get the type of the child element
            // if it is a span then add the text to the subtitle, for a br type add a line return
            string name( child->Name() );
            if( name.compare("tt:span") == 0 )
            {
                subtitlestream << child->GetText();
            }
            else if ( name.compare("tt:br") == 0 )
            {
                subtitlestream << "\n";
            }
        }
        
        string subtitle( subtitlestream.str() );
        if( mCleanSDH )
        {
            removeSDHText( subtitle );
        }
        // Write the subtitle to file
        mSrtWriter->writeSubtitle( begin, end, subtitle );
        
        // get the next subtitle
        element = mEbuReader->nextSubtitle();
    }
    
    mSrtWriter->closeOutputFile();
    return true;
}

bool SrtParser::convertTime(string& time)
{
    // Replace the dot separating the seconds from the milliseconds by a comma
    size_t pos = time.find_last_of('.');
    if( pos == string::npos )
    {
        ERROR("Error in time format.");
        return false;
    }
    time.replace( pos, 1, 1, ',' );
    return true;
}

bool SrtParser::removeSDHText(string& subtitle)
{
    // There is no defined way to add SDH annotations in subtitles so this
    // function can fail if the subtitle creator decided on different conventions.
    
    // Assumptions:
    // SDH text is enclosed in stars or in parenthesis, but not both.
    // There is only one SDH text per subtitle
    
    size_t startpos;
    size_t endpos;
    // Look for stars
    startpos = subtitle.find_first_of( '*', 0 );
    if( startpos != string::npos )
    {
        endpos = subtitle.find_first_of( '*', startpos + 1 );
        if( endpos != string::npos )
        {
            subtitle.replace( startpos, endpos - startpos + 1, "" );
        }
    }
    // look for parenthesis
    else
    {
        startpos = subtitle.find_first_of( '(', 0 );
        if( startpos != string::npos )
        {
            endpos = subtitle.find_first_of( ')', startpos + 1 );
            if( endpos != string::npos )
            {
                subtitle.replace( startpos, endpos - startpos + 1, "" );
            }
        }
    }
    
    // This can leave empty line and extra whitespace, trim them
    startpos = subtitle.find_first_not_of("\n ");
    if( startpos != string::npos )
    {
        endpos = subtitle.find_last_not_of("\n ");
        if( endpos != string::npos )
        {
            subtitle = subtitle.substr( startpos, endpos - startpos + 1 );
        }
        else
        {
            subtitle = subtitle.substr( startpos );
        }
    }
    else // if startpos is not valid there is nothing to keep in this subtitle
    {
        subtitle.clear();
    }
    startpos = subtitle.find( "\n\n" );
    while( startpos != string::npos )
    {
        subtitle.replace( startpos, 2, "\n" );
        startpos = subtitle.find( "\n\n" );
    }
    
    return true;
}

