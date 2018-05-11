# EBU2SRT

ebu2srt is a simple subtitle converter for EBU-TT-D format. This is most notably used by the German public broadcasters. The subtitles are converted to the simple and popular SRT format.

## Usage
```none
   ./ebu2srt  [-c] [--] [--version] [-h] <input> [<output>]
```
Where: 
```none
   -c,  --cleansdh
     Attempts to remove SDH annotations (experimental)

   --,  --ignore_rest
     Ignores the rest of the labeled arguments following this flag.

   --version
     Displays version information and exits.

   -h,  --help
     Displays usage information and exits.

   <input>
     (required)  File to convert from

   <output>
     Converted file, will be derived from input file if not provided
```

## Subtitles
Subtitles in EBU-TT-D are used on the ARD *Mediathek* and the other German public broadcasters. The [MediathekViewWeb](https://mediathekviewweb.de/) is a convenient way to browse the Mediathek.

The specification for the EBU-TT-D Subtitling Distribution Format can be found [here](https://tech.ebu.ch/publications/tech3380).

## Dependencies
[TinyXML2](https://github.com/leethomason/tinyxml2) is used for parsing the XML.

[TCLAP](http://tclap.sourceforge.net/) provides the command line parsing.

## License
ebu2srt is free software: you can redistribute it and/or modify it under the 
terms of the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or any later version. (http://www.gnu.org/licenses/)

