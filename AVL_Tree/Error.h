#pragma once

enum AvlError_t {AVLERR_OK = 0,
                 AVLERR_NOT_INIT,
                 AVLERR_NULL_POINTER_ARG,
                 AVLERR_ARG_ERROR,
                 AVLERR = -1,
                 AVLERR_INSERT
                 };

//TODO:void avlPerror();