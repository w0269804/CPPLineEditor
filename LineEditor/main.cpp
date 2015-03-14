#include <iostream>
#include "DLinkedList.h"
#include "LineEditor.h"
#include <string>

int main(int argc, char **argv) {

    LineEditor editor(argv[1], argv[2]);
    
    for (int nArg=0; nArg < argc; nArg++)
    std::cout << nArg << " " << argv[nArg] <<  std::endl;


    editor.readFile(argv[1]);
  
    /*
     *   editor.showList();
     * 
    // Remove Test
    std::cout << "\n\tTesting remove functionality.\n" << std::endl;
    editor.removeLine(0);
    editor.showList();
    
    // Add Test
    std::cout << "\n\tTesting adding functionality.\n" << std::endl;
    editor.addLine(0, "Beware the Jabberwock, my son!");
    editor.showList();
    
    // Remove Group Test
    std::cout << "\n\tTesting group remove functionality.\n" << std::endl;
    editor.removeLine(0, 4);
    editor.showList();
    
    // Add Front Test
    std::cout << "\n\tTesting no args addLine functionality.\n" << std::endl;
    editor.addLine("The Jabberwocker by Lewis C.");
    editor.showList();
    
    */

    // Test of Get Command
    editor.getCommand();
    
    
    return 0;


}
