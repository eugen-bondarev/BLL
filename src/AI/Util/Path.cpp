#include "Path.h"

namespace AI
{
    namespace Util
    {
        const Str Path::projectRoot = 
#ifdef PROJECT_ROOT_DIR
            PROJECT_ROOT_DIR;
#else
            "";
#endif

        Path::Path(const Str& pathRelativeToProjectRoot)
        {
            (*this) = pathRelativeToProjectRoot;
        }

        Path::Path(const char* pathRelativeToProjectRoot)
        {
            (*this) = pathRelativeToProjectRoot;
        }

        Path::Path(const Path& path)
        {
            (*this) = path;
        }

        Path& Path::operator=(const Str& pathRelativeToProjectRoot)
        {
            fullPath = pathRelativeToProjectRoot;
            return (*this);
        }

        Path& Path::operator=(const char* pathRelativeToProjectRoot)
        {
            fullPath = pathRelativeToProjectRoot;
            return (*this);
        }

        Str Path::Resolve() const
        {
            return projectRoot + "/" + fullPath;
        }
        
        Str Path::operator()() const
        {
            return Resolve();
        }

        Path Path::operator+(const char* string) const
        {
            return fullPath + string;
        }
        
        Path& Path::operator+=(const char* string)
        {
            (*this) = fullPath + string;
            return (*this);
        }
    }
}