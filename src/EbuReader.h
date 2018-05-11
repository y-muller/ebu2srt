/*
 * ebu2srt - Subtitle converter from EBU-TT-D XML to SRT
 * 
 * EbuReader.h
 * 
 * Copyright 2018 Yann Muller
 * 
 * This program is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or any later version. (http://www.gnu.org/licenses/)
 */

#ifndef SRC_EBUREADER_H_
#define SRC_EBUREADER_H_

#include <tinyxml2.h>
#include <string>

using namespace std;
using namespace tinyxml2;

/**
 * @class EbuReader
 * @file EbuReader.h
 * @brief This class reads the subtitle file and provides individual subtitles to the Parser.
 */
class EbuReader
{
public:
    EbuReader();
    virtual ~EbuReader();
        
	/**
	 * @name    readFile
	 * @brief   opens and parses the given EBU subtitle file
	 *
	 * The given input file is open and if in the correct EBU XML format is parsed.
     * The first element is located and the timing offset is checked.
	 *
	 * @param [in] inputfile  the XML file to parse
	 *
	 * @retval true   The file was parsed successfully.
	 * @retval false  Failed to read or parse the file.
	 */
    bool readFile(string& inputfile);
    
	/**
	 * @name    nextSubtitle
	 * @brief   gets the next subtitle as an XML Element
	 *
	 * The subtitle is returned as an XML Element. It can contain several tt:span elements.
     *
	 * @retval XMLElement*   the subtitle element.
	 * @retval nullptr  The last element has been reached or there was a parsing failure.
	 */
    XMLElement* nextSubtitle();

private:
    
    bool fixTimingOffset( string& timestamp );
    
    // The XML document
    XMLDocument* mDoc;

    // subtitle can have a 10 or 20 hour offset !
    int mTimingOffset;
    
    // the next XML element to process
    XMLElement* mNextElement;

};

#endif /* SRC_EBUREADER_H_ */
