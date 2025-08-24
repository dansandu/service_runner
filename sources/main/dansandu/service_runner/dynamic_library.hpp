#pragma once

#include "dansandu/journey/exception.hpp"

#include <memory>
#include <string>

namespace dansandu::service_runner::dynamic_library
{

class CannotLoadLibraryException : public dansandu::journey::exception::Exception
{
public:
    using Exception::Exception;
};

class PRALINE_EXPORT DynamicLibrary
{
public:
    DynamicLibrary();

    explicit DynamicLibrary(const std::wstring& filePath);

private:
    using DeleterType = void (*)(void*);

    std::unique_ptr<void, DeleterType> implementation_;
};

}
