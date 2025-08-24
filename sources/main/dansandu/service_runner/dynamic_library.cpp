#include "dansandu/service_runner/dynamic_library.hpp"

#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

namespace dansandu::service_runner::dynamic_library
{

#ifdef _WIN32
struct Implementation
{
    explicit Implementation(const std::wstring& filePath) : library{LoadLibrary(filePath.c_str())}
    {
        if (library == NULL)
        {
            throw CannotLoadLibraryException{L"Couldn't load library at path '" + filePath + L"'"};
        }
    }

    ~Implementation() noexcept
    {
        FreeLibrary(library);
    }

    HMODULE library;
};
#endif

static void deleteImplementation(void* pointer)
{
    delete static_cast<Implementation*>(pointer);
}

DynamicLibrary::DynamicLibrary() : implementation_{nullptr, deleteImplementation}
{
}

DynamicLibrary::DynamicLibrary(const std::wstring& filePath)
    : implementation_{new Implementation(filePath), deleteImplementation}
{
}

}
