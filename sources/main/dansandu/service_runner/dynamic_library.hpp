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
    DynamicLibrary(const DynamicLibrary&) = delete;

    DynamicLibrary& operator=(const DynamicLibrary&) = delete;

    DynamicLibrary(DynamicLibrary&&) noexcept;

    DynamicLibrary& operator=(DynamicLibrary&&) noexcept;

    DynamicLibrary();

    explicit DynamicLibrary(const std::string& filePath);

    ~DynamicLibrary() noexcept;

private:
    class Implementation;

    std::unique_ptr<Implementation> implementation_;
};

}
