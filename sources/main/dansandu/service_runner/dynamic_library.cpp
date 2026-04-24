#include "dansandu/service_runner/dynamic_library.hpp"
#include "dansandu/journey/exception.hpp"
#include "dansandu/journey/logging.hpp"
#include "dansandu/journey/utility.hpp"

#include <string>

#if defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <dlfcn.h>
#endif

using dansandu::journey::utility::toWideString;

namespace dansandu::service_runner::dynamic_library
{

#if defined(_WIN32)
class Implementation
{
public:
    Implementation(const Implementation&) = delete;
    Implementation(Implementation&&) noexcept = delete;
    Implementation& operator=(const Implementation&) = delete;
    Implementation& operator=(Implementation&&) noexcept = delete;

    explicit Implementation(const std::string& filePath)
        : filePath_{toWideString(filePath)}, library_{LoadLibrary(filePath_.c_str())}
    {
        if (library_ == NULL)
        {
            WTHROW(CannotLoadLibraryException, "Couldn't load library at path '", filePath_, L"'");
        }
        LOG_INFO("Library '", filePath_, "' was loaded");
    }

    ~Implementation() noexcept
    {
        LOG_INFO("Unloading library '", filePath_, "'");
        FreeLibrary(library_);
    }

private:
    std::wstring filePath_;
    HMODULE library_;
};
#elif defined(__linux__)
class Implementation
{
public:
    Implementation(const Implementation&) = delete;
    Implementation(Implementation&&) noexcept = delete;
    Implementation& operator=(const Implementation&) = delete;
    Implementation& operator=(Implementation&&) noexcept = delete;

    explicit Implementation(const std::string& filePath)
        : filePath_{filePath}, library_{dlopen(filePath_.c_str(), RTLD_LAZY)}
    {
        if (library_ == NULL)
        {
            WTHROW(CannotLoadLibraryException, "Couldn't load library at path '", filePath_, "'");
        }
        LOG_INFO("Library '", filePath_, "' was loaded");
    }

    ~Implementation() noexcept
    {
        LOG_INFO("Unloading library '", filePath_, "'");
        dlclose(library_);
    }

private:
    std::string filePath_;
    void* library_;
};
#else
#error "Unknown platform"
#endif

DynamicLibrary::DynamicLibrary() : implementation_{nullptr, [](void*) {}}
{
}

DynamicLibrary::DynamicLibrary(const std::string& filePath)
    : implementation_{new Implementation(filePath), [](void* pointer) { delete static_cast<Implementation*>(pointer); }}
{
}

}
