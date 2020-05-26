//
//  StringFormat.hpp
//  StringFormat
//
//  Created by Paweł Müller on 26/05/2020.
//  Copyright © 2020 Paweł Müller. All rights reserved.
//

#ifndef StringOperations_hpp
#define StringOperations_hpp

#include <iostream>

/**
 Aligns string to given position.
 @param text String you want to align.
 @param choice Type of alignment (0 - left; 1 - right; 2 - center). Defaults to 0 (left).
 @param length Length of space you want to align to. Defaults to 0.
 @param filler A character you want to use instead of whitespace.
 */
std::string stringAlign(std::string text, char choice = 0, unsigned short length = 0, std::string filler = " ");

/**
 Aligns string to center.
 @param text String you want to align.
 @param length Length of space you want to align to.
 @param filler A character you want to use instead of whitespace.
 */
std::string centerString(std::string text, unsigned short length, std::string filler);

/**
 Aligns string to left.
 @param text String you want to align.
 @param length Length of space you want to align to.
 @param filler A character you want to use instead of whitespace.
*/
std::string leftString(std::string text, unsigned short length, std::string filler);

/**
Aligns string to right.
 @param text String you want to align.
 @param length Length of space you want to align to.
 @param filler A character you want to use instead of whitespace.
*/
std::string rightString(std::string text, unsigned short length, std::string filler);

/**
Capitalises string.
 @param text String you want to capitalise.
*/
std::string upperString(std::string text);

/**
Lowercases string.
 @param text String you want to lowercase.
*/
std::string lowerString(std::string text);

/**
Reverses string.
 @param text String you want to reverse.
*/
std::string reverseString(std::string text);

#endif /* StringOperations_hpp */
