#ifndef __AI_Util_Path_h__
#define __AI_Util_Path_h__

#pragma once

#include "../Common.h"

namespace AI
{
    namespace Util
    {
        class Path
        {
        public:
            static const Str projectRoot;

            Path(const char* pathRelativeToProjectRoot);
            Path(const Str& pathRelativeToProjectRoot);
            Path(const Path& path);

            Path& operator=(const Str& pathRelativeToProjectRoot);
            Path& operator=(const char* pathRelativeToProjectRoot);
            Path operator+(const char* string) const;
            Path& operator+=(const char* string);
            
            Str Resolve() const;
            Str operator()() const;

        private:
            Str fullPath;
        };
    }
}

#endif