//
//  StringFormat.cpp
//  StringFormat
//
//  Created by Paweł Müller on 26/05/2020.
//  Copyright © 2020 Paweł Müller. All rights reserved.
//

#include "StringOperations.hpp"

#include <string>

std::string stringAlign(std::string text, char choice, unsigned short length, std::string filler) {
    if (text.length() == 0 or text.length() == length) return text;
    else if (text.length() > length) return text.substr(0, length);
    else {
        enum Alignments{left, right, center};
        switch(choice) {
            default: case left:     return leftString(text, length, filler); break;
            case right:             return rightString(text, length, filler); break;
            case center:            return centerString(text, length, filler); break;
        }
    }
    return "";
}

std::string centerString(std::string text, unsigned short length, std::string filler) {
    unsigned short textLength = text.size(), spaceCount = (length - textLength) / 2;
    std::string output = "";
    
    for (int i = 0; i < spaceCount; i++) output += filler;
    output += text;
    for (int i = 0; i < length - spaceCount - textLength; i++) output += filler;
    
    return output;
}

std::string leftString(std::string text, unsigned short length, std::string filler) {
    unsigned short textLength = text.size(), spaceCount = length - textLength;
    std::string output = "";
    
    output += text;
    for (int i = 0; i < spaceCount; i++) output += filler;
    
    return output;
}

std::string rightString(std::string text, unsigned short length, std::string filler) {
    unsigned short textLength = text.size(), spaceCount = length - textLength;
    std::string output = "";

    for (int i = 0; i < spaceCount; i++) output += filler;
    output += text;
    
    return output;
}

std::string upperString(std::string text) {
    for (auto & character: text) character = toupper(character);
    return text;
}

std::string lowerString(std::string text) {
    for (auto & character: text) character = tolower(character);
    return text;
}

std::string reverseString(std::string text) {
    std::string new_string = "";
    for (int i = text.length() - 1; i >= 0; i--) new_string += text[i];
    return new_string;
}
