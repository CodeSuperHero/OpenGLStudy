#pragma once
#include <iostream>

class FileUtil final
{
public:
    static char* Read(const char *fn);

    static int Write(const char * fn, const char * s);

public:
};