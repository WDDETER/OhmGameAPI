//
//      Jaidev Bormann
//


#include <stdio.h>
#include <stdarg.h>

#include "OGA_error.h"
#include "OGA_types.h"


#define OGA_ERROR_MESSAGE_SIZE_ 512


#if defined(_MSC_VER)

    #define OGA_THREAD_LOCAL_ __declspec(thread)

#else

    #define OGA_THREAD_LOCAL_ __thread

#endif



struct OGA_error_ {

        OGA_errors      code;
        char            message[OGA_ERROR_MESSAGE_SIZE_];

};

static OGA_THREAD_LOCAL_ struct OGA_error_ error_singleton_ = {

        .code           = OGA_SUCCESS,
        .message        = "OGA Success"

};


void OGA_error_clear(void) {

        error_singleton_.code = OGA_SUCCESS;
        snprintf(error_singleton_.message, sizeof(error_singleton_.message), "OGA Success");

}

OGA_errors      OGA_error_get_code      (void)  { return error_singleton_.code; }
constptr_string OGA_error_get_message   (void)  { return error_singleton_.message; }

void OGA_error_set_(OGA_errors code, constptr_string format, ...) {     // one problem, this does leak a OGA internal. Don't know how to fix it. Maybe not a problem.

        error_singleton_.code = code;

        va_list args;
        va_start(args, format);

        vsnprintf(error_singleton_.message, sizeof(error_singleton_.message), format, args);

        va_end(args);

}