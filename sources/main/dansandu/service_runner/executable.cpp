#include "dansandu/journey/exception.hpp"
#include "dansandu/journey/utility.hpp"
#include "dansandu/service_runner/dynamic_library.hpp"
#include "dansandu/service_runner/error_code.hpp"
#include "dansandu/service_runner/service_registry.hpp"

#include <iostream>

using dansandu::journey::exception::Exception;
using dansandu::journey::utility::toWideString;
using dansandu::service_runner::dynamic_library::DynamicLibrary;
using dansandu::service_runner::error_code::ErrorCode;
using dansandu::service_runner::service_registry::ServiceRegistry;

int main(const int argumentCount, const char* const* const arguments)
{
    auto library = DynamicLibrary{};

    try
    {
        if (argumentCount <= 1)
        {
            std::cerr << "Aborting because no library file path was supplied to load." << std::endl;
            return ErrorCode::libraryPathNotSupplied;
        }
        else if (argumentCount <= 2)
        {
            std::cerr << "Aborting because no service identifier was supplied." << std::endl;
            return ErrorCode::serviceIdentifierNotSupplied;
        }

        library = DynamicLibrary{toWideString(arguments[1])};

        const auto invoker = ServiceRegistry::getServiceInvoker(arguments[2]);

        return invoker(argumentCount - 3, arguments + 3);
    }
    catch (const Exception& exception)
    {
        std::wcerr << "Wide exception was thrown with message: " << exception.message() << std::endl;
        return ErrorCode::wideExceptionThrown;
    }
    catch (const std::exception& exception)
    {
        std::cerr << "Ascii exception was thrown with message: " << exception.what() << std::endl;
        return ErrorCode::asciiExceptionThrown;
    }

    return ErrorCode::none;
}
