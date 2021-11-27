#ifndef __AI_Network_h__
#define __AI_Network_h__

#pragma once

#include "NetworkDescriptor.h"
#include "Layer.h"

namespace AI
{
    // Eine Forward-declaration, weil es die Klasse Matrix noch gar nicht gibt.
    class Matrix;

    class Network
    {
    public:
        Network(const NetworkDescriptor& descriptor);

        // Eingabe (in unserem Fall eine flache 28x28-Matrix, also eine 784x1-Matrix)
        Matrix Feedforward(const Matrix& input);
    };
}

#endif