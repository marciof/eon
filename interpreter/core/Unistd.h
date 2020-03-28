/**
 * Wrapper over `unistd.h` to include definitions that may be missing in some
 * environments.
 */

#pragma once

/**
 * @see https://docs.microsoft.com/cpp/preprocessor/predefined-macros
 */
#ifdef _MSC_VER

#include <io.h>
#include <stdio.h>

/**
 * @see https://docs.microsoft.com/cpp/c-runtime-library/reference/fileno
 */
#define STDIN_FILENO (_fileno(stdin))

/**
 * @see https://docs.microsoft.com/cpp/c-runtime-library/reference/read
 */
#define read _read

#else
#include <unistd.h>
#endif
