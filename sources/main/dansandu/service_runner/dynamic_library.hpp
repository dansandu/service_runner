#pragma once

#include "dansandu/journey/exception.hpp"

#include <memory>
#include <string>

namespace dansandu::service_runner::dynamic_library
{

class CannotLoadLibraryException : public dansandu::journey::exception::WideException
{
public:
    using WideException::WideException;
};

class PRALINE_EXPORT DynamicLibrary
{
public:
    DynamicLibrary();

    explicit DynamicLibrary(const std::string& filePath);

private:
    using DeleterType = void (*)(void*);

    std::unique_ptr<void, DeleterType> implementation_;
};

}
