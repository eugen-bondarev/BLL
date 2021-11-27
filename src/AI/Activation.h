#ifndef __AI_Activation_h__
#define __AI_Activation_h__

#pragma once

#include "Common.h"

namespace AI
{
    struct Activation
    {
        Function g;
    };

    // Die am weitesten verbreitete Aktivierungsfunktion - Sigmoid (ist in Activation.cpp implementiert).
    extern Activation sigmoid;
}

#endif