/*
 * ebu2srt - Subtitle converter from EBU-TT-D XML to SRT
 * 
 * EbuReader.cpp
 * 
 * Copyright 2018 Yann Muller
 * 
 * This program is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or any later version. (http://www.gnu.org/licenses/)
 */

#include "EbuReader.h" 
#include "Print.h"
#include <string>
#include <iostream>

using namespace std;
using namespace tinyxml2;

EbuReader::EbuReader() :
    mNextElement(nullptr), mTimingOffset(0), mDoc(nullptr)
{
}

EbuReader::~EbuReader()
{
    if( mDoc )
    {
        delete mDoc;
    }
}

bool EbuReader::readFile(string& inputfile)
{
    XMLError ret;
    
    // open the XML file, it is automatically parsed
    mDoc = new XMLDocument;
    ret = mDoc->LoadFile( inputfile.c_str() );
    
    if( ret != XML_SUCCESS )
    {
        DEBUG( "LoadFile failed: " << inputfile );
        return false;
    }
    DEBUG( "LoadFile success" );

    // find the first subtitle element
    mNextElement = mDoc->FirstChildElement("tt:tt")->FirstChildElement("tt:body")->FirstChildElement("tt:p");
    if( mNextElement == NULL)
    {
        mNextElement = mDoc->FirstChildElement("tt:tt")->FirstChildElement("tt:body")->FirstChildElement("tt:div")->FirstChildElement("tt:p");
    }
    if( mNextElement == NULL)
    {
        ERROR("Document structure not as expected. Aborting.");
        return false;
    }
    else
    {
        // check for timing offset
        // The EBU spec allows for an offset of 10 hours (often used) or of 20 hours.
        const char* begin = mNextElement->Attribute( "begin" );
        if( strncmp( begin, "10:", 3 ) == 0 )
        {
            mTimingOffset = 10;
            DEBUG( "Timing offset of 10 hours." );
        }
        if( strncmp( begin, "20:", 3 ) == 0 )
        {
            mTimingOffset = 20;
            DEBUG( "Timing offset of 20 hours." );
        }
    }

    return true;
}

XMLElement* EbuReader::nextSubtitle()
{
    XMLElement* retElement = mNextElement;
    // Check if we have reached the last element
    if( mNextElement == NULL )
    {
        return nullptr;
    }

    // Move nextElement to the next position
    mNextElement = mNextElement->NextSiblingElement("tt:p");
    
    // Fix timings according to offset
    if( mTimingOffset != 0 )
    {
        string begin( retElement->Attribute( "begin" ) );
        fixTimingOffset(begin);
        retElement->SetAttribute( "begin", begin.c_str() );
        
        string end( retElement->Attribute( "end" ) );
        fixTimingOffset(end);
        retElement->SetAttribute( "end", end.c_str() );
    }
    return retElement;
}

bool EbuReader::fixTimingOffset(string& timestamp)
{
    // Remove the 10 or 20 hour offset 
    // Extract the hour from the timestamp, correct it and place it back
    int pos = timestamp.find_first_of(":");
    int hour = stoi(timestamp.substr(0, pos), nullptr) - mTimingOffset;
    string timestampNew( to_string(hour) + timestamp.substr(pos));
    timestamp = timestampNew;

    return true;
}
