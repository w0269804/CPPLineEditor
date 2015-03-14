#include "LineEditor.h"

LineEditor::LineEditor()
{
    curLine = 0;
    quit = false;
}

// constructor()
// sets the in and outfiles for writing and reading
LineEditor::LineEditor(char* inFile, char* outFile)
{
    curLine = 0;
    this->inFile = inFile;
    this->outFile = outFile;
    quit = false;
}

// destructor ~()
// TODO make this virtual
LineEditor::~LineEditor()
{

}

// writeFile()
// =====================================
// Writes the contents to the outfile
// =====================================
void LineEditor::writeFile()
{
    // open file for overwrite
    outStream.open(outFile, std::ios::trunc);

    // check if open to avoid exception
    if (outStream.is_open()) {
        for(int i = 0; i < list.size(); i++)
            outStream << list.getAt(i) << std::endl;
    }
    // close the stream
    outStream.close();
    
}

// readFile()
// =====================================
// Reads the lines of a file into
// a custom double linked list
// =====================================
void LineEditor::readFile(const char* fileName)
{
    inStream.open(fileName); // open file

    // check if the stream is open
    if (inStream.is_open()) {
        while (!inStream.eof()) {
            char * line = new char[LINE_LENGTH]; // hold current line
            inStream.getline(line, LINE_LENGTH); // store textfile line
            list.addBack(line); // push the line to the back of the list
        }
    }

    inStream.close();
}

// removeLine(line)
// =====================================
// Removes line n from the list.
// =====================================
void LineEditor::removeLine(int line)
{
        list.remove(line);
}

// addLine(int, char *)
// =====================================
// Adds line to the list of lines at
// position n.
//======================================
void LineEditor::addLine(int lineNum, char * line)
{
    //if(lineNum >= 0 || lineNum < list.size())
    list.addAt(line, lineNum);

}

// addLine(char *)
// =====================================
// Adds the line to the back of the list
// i.e., at position 0.
// =====================================
void LineEditor::addLine(char* line)
{
    list.addBack(line);
}

// removeLine(int, int)
// =====================================
// Removes all lines from i to n from the
// list of lines.
// =====================================
void LineEditor::removeLine(int start, int end)
{
    list.remove(start, end);
}

// showList()
// =====================================
// Displays the contents of the list to
// the standard outstream.
// =====================================
void LineEditor::showList()
{
    std::cout << list;
}


void LineEditor::showList(int line)
{
    std::cout <<  "#" << line << "# " <<  list.getAt(line) << std::endl;
}

// showList(int s, int e)
// =====================================
// show subset of list contents starting
// from s throught to e.
// =====================================
void LineEditor::showList(int start, int end)
{
    if(start == end) {
        // if start = end simply display the line
        std::cout << "#" << start << "# " << list.getAt(start) << std::endl;
    }
    else
    {
        // print out all lines in range
        for(int j = start; j <= end; j++)
            std::cout << "#" << j << "# " << list.getAt(j) << std::endl;
    }
}

// getCommand()
// =====================================
// Gets command from user and processes it.
// Validation is handled by the function
// which processes it. If the command does
// not exist then no action is taken.
// =====================================
void LineEditor::getCommand()
{
    try {
        do {
	  
	  if(quit)
	    break;
	  
            std::cin.clear();
            std::cout  << curLine << "-->"; // line marker
            std::cin >> command; // store the command

            if(!validCommand(command)) {
                system("cls"); // clear the screen
                std::cout << "Invalid Command!" << std::endl;
                getCommand();
            }

            system("cls"); // clear the screen
	    processCommand(command);

        } while(!quit); // process command

        system("cls"); // clear the screen

    } catch (IndexOutOfBounds e) {
        std::cout << e.getMessage() << std::endl;
        getCommand();
    }

}

// processCommand(char *)
// =====================================
// Determines if the command has arguments
// or not and sends it to the appropriate
// function.
// =====================================
void LineEditor::processCommand(const char* c)
{
    int length = std::strlen(c);
   
    if(length == 1) {
        noArgCommand(c);
    }
    else
        argCommand(c);

}

// noArgCommand(char *)
// =====================================
// Handles commmands which have no range
// and no numeric argument.
// =====================================
void LineEditor::noArgCommand(const char* c)
{
    char command = toupper(c[0]);

    switch (command)
    {

    case 'D':
        list.remove(curLine);
        break;

    case 'E':
        writeFile();
	quit = true;
        break;
    case 'G':
        curLine = 0;
        break;

    case 'V':
        showList();
        break;

    case 'L':
        showList(curLine);
        break;

    case 'i':
    case 'I':
    {
        char * newLine = new char[LINE_LENGTH];
        std::cout << "Enter Line: ";
        std::cin.ignore(); // to prevent reading in the whitespace with getline;
        std::cin.getline(newLine, LINE_LENGTH);
        addLine(curLine, newLine);
    }
    break;

    case 'q':
    case 'Q':
      quit = true;
      std::cout << "Exiting.";
    break;
    
    case 's':
    case 'S':
    {
        char * newLine = new char[LINE_LENGTH];
        std::cout << "Enter Substitute Line: ";
        std::cin.ignore(); // to prevent reading in the whitespace with getline;
        std::cin.getline(newLine, LINE_LENGTH);
        removeLine(curLine);
        addLine(curLine, newLine);
    }
    break;

    default:
        std::cout << "Unknown command or missing parameter." << std::endl;

    }
}

// argCommand(char *)
// =====================================
// Handles commands with a numeric modifier
// either a range or a single number
// =====================================
void LineEditor::argCommand(const char* c)
{
    int length = std::strlen(c); 	// the length of the string

    int rangePosition = 0;		// the position in string where range starts
    bool hasRange = false;		// whether there is a range of numbers

    int startLine = 0; 			// for holding the range
    int endLine = 0;

    // check for a range delimiter
    for(int i = 0; i < length; i++) {
        if(c[i] == RANGE_DELIM) {
            rangePosition = i;
            hasRange = true;
            break;
        }
    }

    if(!hasRange) {

        std::memcpy(command, c, length-1); // make a copy of array to avoid manipulating command
        startLine = atoi(subChars(command, 1, length-1)); // get substring from command to end of number
        argCommand(c, startLine);

    } else {
        // parse out start line
        std::memcpy(command, c, length-1); // make a copy of array to avoid manipulating command
        startLine = atoi(subChars(command, 1, rangePosition)); // get substring

        // parse out end line
        std::memcpy(command, c, length-1); // make a copy of array to avoid manipulating command
        endLine = atoi(subChars(command, rangePosition+1, length)); // get substring

        argCommand(c, startLine, endLine);
    }

}

// argCommand(c, lineNum)
// =====================================
// Handles single commands with a line number specified
// =====================================
void LineEditor::argCommand(const char* c, int line)
{

    char command = toupper(c[0]);

    switch (command) {

    case 'D':
        removeLine(line);
        break;
    case 'G':
        if(line >= 0 && line < list.size())
            curLine = line;
        break;
	
    case 'V':
        break;
	
    case 'L':
        showList(line);
        break;
	
    case 'I':  
        addLine(line, getLine());
	break;
   
    case 'S':
        removeLine(line);
        addLine(line, getLine());
	break;
    
    default:
        std::cout << "Unknown command or missing parameter." << std::endl;
    }

}

// argCommand(c, start, end)
// =====================================
// Used to handle commands which have a range
// such as delete or list.
// =====================================
void LineEditor::argCommand(const char* c, int start, int end)
{
    switch (c[0]) {

    case 'D':
    case 'd':
        list.remove(start, end);
        break;
	
    case 'L':
    case 'l':
        showList(start, end);
        break;
	
    default:
        std::cout << "Unknown command or missing parameter." << std::endl;
    }
}

// getLine()
// =====================================
// Helper method to get line for subbing
// in lines or inserting new lines.
// =====================================
char* LineEditor::getLine()
{
    char * newLine = new char[LINE_LENGTH];
    std::cout << "Enter Line: ";
    std::cin.ignore(); // to prevent reading in the whitespace with getline;
    std::cin.getline(newLine, LINE_LENGTH);

    return newLine;
}

// subChars();
// =====================================
// Returns a new substring of characters from
// x to y. Used to parse out commands issued.
// REFERENCE
// http://paul.grozav.info/2012/12/10/c-substring-on-char-array/
// =====================================
char* LineEditor::subChars(char* str, short int x, short int y)
{   char* ret = new char[y+1];
    for(short i=x; i<x+y; i++)
        ret[i-x]=str[i];
    ret[y] = '\0';
    return ret;

}


// validCommand()
// =====================================
// Uses the boost regex library to check
// for valid commands. TODO These should
// defined as constants and maybe use
// some sort of looping structure to
// check
// =====================================
bool LineEditor::validCommand(char * com) const
{

    // check for 0 length strings
    if(std::strlen(com) == 0)
        return false;

    // check for single matches
    if(std::strlen(com) == 1) {
        regex a("((A|D|E|G|V|L|I|S|Q){1})", boost::regex::icase); // check single digit commands
        return(regex_match(com, a));
    }

    // all other valid patterns
    regex b("((A|D|E|G|V|L|I|S)[0-9])?", boost::regex::icase);
    regex c("((A|D|E|G|V|L|I|S)([1-9])(([0-9])+)?)", boost::regex::icase);
    regex d("((A|D|E|G|V|L|I|S)[0-9]+-[0-9])", boost::regex::icase);

    return(regex_match(com, b) || regex_match(com,c) || regex_match(com,d));


}

