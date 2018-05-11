/*
 * ebu2srt - Subtitle converter from EBU-TT-D XML to SRT
 * 
 * Debug.h
 * 
 * Copyright 2018 Yann Muller
 * 
 * This program is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or any later version. (http://www.gnu.org/licenses/)
 */

// Add -DDEBUGMODE to CXXFLAGS to enable debug output

#ifndef SRC_PRINT_H_
#define SRC_PRINT_H_

#include <iostream>

#define PRINT(x) do { std::cout << x << std::endl; } while (0)

#define ERROR(x) do { std::cerr << x << std::endl; } while (0)

    
#ifdef DEBUGMODE

    #define DEBUG(x) do { std::cerr << "debug: " << x << std::endl; } while (0)

#else // no DEBUG

    #define DEBUG(x)

#endif

#endif /* SRC_PRINT_H_ */
