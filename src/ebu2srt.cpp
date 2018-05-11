/*
 * ebu2srt - Subtitle converter from EBU-TT-D XML to SRT
 * 
 * Copyright 2018 Yann Muller
 * 
 * This program is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or any later version. (http://www.gnu.org/licenses/)
 */

#include <tclap/CmdLine.h>
#include <string>
#include <iostream>
#include "EbuReader.h"
#include "SrtParser.h"
#include "SrtWriter.h"
#include "Print.h"

using namespace std;

int main(int argc, char **argv)
{
    std::string inputfile;
    std::string outputfile;
    bool cleansdh;

    // command line parsing with TCLAP
    try
    {
        TCLAP::CmdLine cmd("Converts EBU subtitles to SRT", ' ', "0.5.0");
        // inputfile - mandatory argument
        TCLAP::UnlabeledValueArg<std::string> inputfileArg("inputfile", "File to convert from", true, "", "string");
        cmd.add( inputfileArg );
        // outputfile - optional, will be derived from inputfile if not specified
        TCLAP::UnlabeledValueArg<std::string> outputfileArg("outputfile", "Converted file", false, "", "string");
        cmd.add( outputfileArg );
        // cleansdh - optional flag
        TCLAP::SwitchArg cleansdhSwitch("c", "cleansdh", "Attempts to remove SDH annotations (experimental)", cmd, false);    

        cmd.parse( argc, argv );
        
        // get the command line values
        inputfile = inputfileArg.getValue();
        outputfile = outputfileArg.getValue();
        cleansdh = cleansdhSwitch.getValue();
    }
    catch(TCLAP::ArgException &e)
    {
        ERROR( "Argument parsing error: " << e.error() << " for arg " << e.argId() );
    }
        
    // check arguments
    DEBUG( "in:  " << inputfile );
    if( outputfile.empty() )
    {
        // Output file not provided, use input file name after changing the file extension
        // unless the last dot on the inputfile is too far from the end (probably not a valid extension)
        int extPos = inputfile.find_last_of('.');
        if( (inputfile.length() - extPos) > 6 )  // arbitrary decision on how long an extension should be
        {
            outputfile = inputfile + ".srt";
        }
        else
        {
            outputfile = inputfile.substr( 0, extPos ) + ".srt";
        }
    }
    DEBUG( "out: " << outputfile );
        
    // subtitle processing
    EbuReader reader;
    if( reader.readFile( inputfile ) == false )
    {
        ERROR( "Failed to read and parse input file: " << inputfile );
        return 1;
    }

    SrtWriter writer;
    if( writer.openOutputFile( outputfile ) == false )
    {
        ERROR( "Failed to open the output file: " << outputfile );
        return 1;
    }
    
    SrtParser parser = SrtParser( &reader, &writer );
    parser.setSDHCleaning( cleansdh );
    parser.parseSubtitles();
    
    return 0;
}
