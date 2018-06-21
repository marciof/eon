#pragma once
#include <errno.h>
#include "../core/Err.h"

void k_Err_describe_errno(struct k_Err* err);

#define K_ERR_SET_ERRNO(err, num) \
    K_ERR_SET((err), k_Err_describe_errno, (num))