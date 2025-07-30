#pragma once

namespace dansandu::service_runner::error_code
{

enum ErrorCode : int
{
    none = 0,
    libraryPathNotSupplied = 1,
    serviceIdentifierNotSupplied = 2,
    asciiExceptionThrown = 3,
    wideExceptionThrown = 4,
};

}
