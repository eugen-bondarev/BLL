#ifndef __AI_Activation_h__
#define __AI_Activation_h__

#pragma once

#include <functional>
#include "Common.h"

namespace AI
{
    // Funktion im mathematischen Sinne.
    using Function = std::function<Num(Num x)>;

    struct Activation
    {
        Function g;
    };

    // Die am weitesten verbreitete Aktivierungsfunktion - Sigmoid (ist in Activation.cpp implementiert).
    extern Activation sigmoid;
}

#endif