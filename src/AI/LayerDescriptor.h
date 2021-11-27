#ifndef __AI_LayerDescriptor_h__
#define __AI_LayerDescriptor_h__

#pragma once

#include "Activation.h"

namespace AI
{
    struct LayerDescriptor
    {
        size_t numNeurons;

        // Mathematische Funktion f(x).
        Activation g {sigmoid};
    };
}

#endif