/*
 * Copyright 2015 <copyright holder> <email>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef LINEEDITOR_H
#define LINEEDITOR_H

#include "DLinkedList.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <boost/regex.hpp>                           /* RegEx                   Boost  */

using boost::regex; /* GNU Compiler Doesn't have REGEX so I brought in BOOST */
using boost::regex_match;

const int LINE_LENGTH = 100;
const char RANGE_DELIM = '-';

class LineEditor
{
public:
    LineEditor();
    ~LineEditor();

    LineEditor(char * inFile, char * outFile);

    void readFile(const char * fileName);
    void writeFile();

    void addLine(int lineNum, char * line);
    void addLine(char * line);

    void removeLine(int line); // remove single line
    void removeLine(int startLine, int endLine); // remove subset of lines

    void showList(); // show all lines
    void showList(int start, int end); // show line subset
    void showList(int line);
    
    void getCommand(); // get command from user
    
    bool validCommand(char *) const; // checks to see if command is valid



private:

    char* subChars(char* str, short x, short y);

    // parse and process commands
    void processCommand(const char * command);
    void noArgCommand(const char * command);
    void argCommand(const char * command);
    void argCommand(const char * c, int line);
    void argCommand(const char *, int start, int end);

    // get line for substituting and inserting
    char * getLine();
    
    bool quit;
    
    int curLine;
    char command[100];
    
    char * inFile;
    char * outFile;
    
    DLinkedList list; // list to hold entries
    std::ofstream outStream; // stream to write file
    std::ifstream inStream; // stream to read file
};

#endif // LINEEDITOR_H
