#pragma once

#include "dansandu/journey/macro.hpp"

#include <map>
#include <mutex>
#include <string>
#include <vector>

namespace dansandu::service_runner::service_registry
{

class PRALINE_EXPORT ServiceRegistry
{
public:
    ServiceRegistry(const ServiceRegistry&) = delete;
    ServiceRegistry(ServiceRegistry&&) noexcept = delete;
    ServiceRegistry& operator=(const ServiceRegistry&) = delete;
    ServiceRegistry& operator=(ServiceRegistry&&) noexcept = delete;

    using ServiceInvokerType = int (*)(const int argumentCount, const char* const* const arguments);

    static ServiceRegistry& getGlobalInstance();

    int registerServiceInvoker(const std::string& serviceIdentifier, const ServiceInvokerType serviceInvoker);

    ServiceInvokerType getServiceInvoker(const std::string& serviceIdentifier);

    std::vector<std::string> getServiceNames();

private:
    ServiceRegistry();

    std::map<std::string, ServiceRegistry::ServiceInvokerType> services;
    std::mutex servicesMutex;
};

#define DANSANDU_SERVICE_RUNNER_REGISTER_SERVICE(identifier, invoker)                                                  \
    static int DANSANDU_JOURNEY_UNIQUE_NAME =                                                                          \
        dansandu::service_runner::service_registry::ServiceRegistry::getGlobalInstance().registerServiceInvoker(       \
            identifier, invoker)

}
