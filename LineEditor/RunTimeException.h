#ifndef RUNTIMEEXCEPTION_H
#define RUNTIMEEXCEPTION_H

#include <string>
using std::string;

class RunTimeException
{
public:
    RunTimeException(const string &err) { errorMessage = err; }
    ~RunTimeException();
    
    string getMessage() { return errorMessage; }
    
private: 
  
  string errorMessage;
  
};

#endif // RUNTIMEEXCEPTION_H
