#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    DWORD processId;
    HANDLE fakeProcessHandle;
    HANDLE trueDuplicateProcessHandle;
    HANDLE trueOpenProcessHandle;

    processId = GetCurrentProcessId();
    fakeProcessHandle = GetCurrentProcess();

    if(DuplicateHandle(fakeProcessHandle,
                       fakeProcessHandle,
                       fakeProcessHandle,
                       &trueDuplicateProcessHandle,
                       0,
                       TRUE,
                       DUPLICATE_SAME_ACCESS))
    {
        printf("DuplicateHandle succesfuly create copy of Handle.\n");


    }else{
        printf("DuplicateHandle ERROR.\n");
    };

    if(CloseHandle(trueDuplicateProcessHandle)){
        printf("DuplicateHandle copy of Handle closed.\n");
    }else{
        printf("DuplicateHandle close ERROR.\n");
    };

    trueOpenProcessHandle = OpenProcess(PROCESS_ALL_ACCESS,TRUE,processId);
    if(trueOpenProcessHandle){
        printf("OpenProcess succesfuly create copy of Handle.\n");
    }else{
        printf("OpenProcess ERROR.\n");
    };

    if(CloseHandle(trueOpenProcessHandle)){
        printf("OpenProcess copy of Handle closed.\n");
    }else{
        printf("OpenProcess close ERROR.\n");
    };
    return 0;
};