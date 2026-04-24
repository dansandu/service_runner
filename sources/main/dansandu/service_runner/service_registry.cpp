#include "dansandu/service_runner/service_registry.hpp"
#include "dansandu/journey/exception.hpp"

#include <map>
#include <mutex>
#include <stdexcept>
#include <string>

namespace dansandu::service_runner::service_registry
{

ServiceRegistry::ServiceRegistry()
{
}

ServiceRegistry& ServiceRegistry::getGlobalInstance()
{
    static auto serviceRegistry = ServiceRegistry{};
    return serviceRegistry;
}

int ServiceRegistry::registerServiceInvoker(const std::string& serviceIdentifier,
                                            const ServiceInvokerType serviceInvoker)
{
    const auto lock = std::lock_guard<std::mutex>(servicesMutex);
    const auto position = services.find(serviceIdentifier);
    if (position != services.end())
    {
        THROW(std::logic_error, "Identifier '", serviceIdentifier, "' is used by another service");
    }
    services.insert({serviceIdentifier, serviceInvoker});
    return 0;
}

ServiceRegistry::ServiceInvokerType ServiceRegistry::getServiceInvoker(const std::string& identifier)
{
    const auto lock = std::lock_guard<std::mutex>(servicesMutex);
    const auto position = services.find(identifier);
    if (position == services.end())
    {
        THROW(std::logic_error, "No service was registered with identifier '", identifier, "'");
    }
    return position->second;
}

std::vector<std::string> ServiceRegistry::getServiceNames()
{
    const auto lock = std::lock_guard<std::mutex>(servicesMutex);

    auto result = std::vector<std::string>{};
    result.reserve(services.size());

    for (const auto& entry : services)
    {
        result.push_back(entry.first);
    }

    return result;
}

}
