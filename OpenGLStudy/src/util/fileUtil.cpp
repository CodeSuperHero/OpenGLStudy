#include "util/FileUtil.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


char* FileUtil::Read(const char *fn)
{
    FILE *fp;
    char *content = nullptr;
    size_t count = 0;
    if (nullptr != fn)
    {
        auto err = fopen_s(&fp, fn, "r");
        if (nullptr != fp)
        {
            fseek(fp, 0, SEEK_END);
            count = ftell(fp);
            rewind(fp);
            if (count > 0)
            {
                content = new char[count + 1];
                count = fread(content, sizeof(char), count, fp);
                content[count] = '\0';
            }
            fclose(fp);
        }
    }

    return content;
}


int FileUtil::Write(const char *fn, const char *s)
{
    FILE *fp;
    int status = 0;
    if (nullptr != fn) {
        auto err = fopen_s(&fp, fn, "w");
        if (nullptr != fp) {
            if (fwrite(s, sizeof(char), strlen(s), fp) == strlen(s))
                status = 1;
            fclose(fp);
        }
    }
    return(status);
}


