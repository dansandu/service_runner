#include "dansandu/journey/exception.hpp"
#include "dansandu/journey/utility.hpp"
#include "dansandu/service_runner/dynamic_library.hpp"
#include "dansandu/service_runner/service_registry.hpp"

#include <iostream>

using dansandu::journey::exception::wrapInTryCatch;
using dansandu::journey::utility::toWideString;
using dansandu::service_runner::dynamic_library::DynamicLibrary;
using dansandu::service_runner::service_registry::ServiceRegistry;

int main(const int argumentCount, const char* const* const arguments)
{
    if (argumentCount <= 1)
    {
        std::cerr << "Aborting because no test library file path was supplied." << std::endl;
        return 1;
    }
    else if (argumentCount <= 2)
    {
        std::cerr << "Aborting because no service identifier was supplied." << std::endl;
        return 2;
    }

    const auto testLibrary = DynamicLibrary{toWideString(arguments[1])};

    const auto invoker = ServiceRegistry::getServiceInvoker(arguments[2]);

    wrapInTryCatch(invoker, argumentCount - 3, arguments + 3);

    return 0;
}
