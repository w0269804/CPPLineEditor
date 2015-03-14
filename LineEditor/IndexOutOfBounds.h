#ifndef INDEXOUTOFBOUNDS_H
#define INDEXOUTOFBOUNDS_H
#include "RunTimeException.h"

class IndexOutOfBounds : public RunTimeException
{
public:
    IndexOutOfBounds(const string &err = "Index out of bounds.");
    ~IndexOutOfBounds();
};

#endif // INDEXOUTOFBOUNDS_H
