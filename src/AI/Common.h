#ifndef __AI_Common_h__
#define __AI_Common_h__

#pragma once

#include <functional>
#include <iostream>
#include <vector>
#include <string>

namespace AI
{
    using Num = float;

    template <typename T>
    using Vec = std::vector<T>;

    using Str = std::string;

    // Funktion im mathematischen Sinne.
    using Function = std::function<Num(Num x)>;

    #define LINE_OUT(x)\
        std::cout << x << '\n'

    #define VAR_OUT(x)\
        std::cout << #x << " = " << x << '\n'

    /* 
    * Die Funktion wurde kopiert von:
    * https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
    * Ich habe sie zwecks bequemeren Debuggings kopiert, um Strings leichter zu bearbeiten, bspw. für Ausgabe.
    * Lizenz: CC0 1.0
    */
    template <typename... Args>
    std::string StringFormat(const std::string &format, Args... args)
    {
        int size_s = std::snprintf(nullptr, 0, format.c_str(), args...) + 1;
        if (size_s <= 0)
        {
            throw std::runtime_error{ "Error during formatting." };
        }

        const size_t size = static_cast<size_t>(size_s);
        const std::unique_ptr<char[]> buf = std::make_unique<char[]>(size);
        std::snprintf(buf.get(), size, format.c_str(), args...);
        return std::string(buf.get(), buf.get() + size - 1);
    }
}

#endif