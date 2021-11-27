#ifndef __AI_Network_h__
#define __AI_Network_h__

#pragma once

#include "NetworkDescriptor.h"
#include "Layer.h"

namespace AI
{
    class Network
    {
    public:
        Network(const NetworkDescriptor& descriptor);
    };
}

#endif