#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_

#include "PhysicsEngine.h"

char get_key_presses()
{
    // FROM:
    // https://stackoverflow.com/questions/421860/capture-characters-from-standard-input-without-waiting-for-enter-to-be-pressed

    char character = 0;
    #if defined(_WIN32)
    character = _getch();
    #elif __linux__
    if (read(0, &character, 1) < 0)
    {
        perror("read()");
    }
    #endif

    return character;
}

#endif // _MAIN_H_
