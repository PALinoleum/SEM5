#include "windows.h"
#include "base.h"

char* getComputerNameMY(){
    char str[4096];
    DWORD size = 4096;
    char* result_str;
    if(GetComputerNameA(str, &size)){
        result_str = str;
    }
    else{
        result_str = "ERROR";
    }
    return result_str;
};
