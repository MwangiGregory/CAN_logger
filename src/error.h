#ifndef ERROR_H
#define ERROR_H

#include <Arduino.h>
#include "application.h"

enum class ErrCode
{
    NONE,
    UNKNOWN,
    INIT_ERROR,
    READ_ERROR,
    WRITE_ERROR,
    TIMEOUT_ERROR,
    CONNECTION_ERROR
};

enum class ErrLevel
{
    LEVEL_NONE,
    LEVEL_LOW,
    LEVEL_MEDIUM,
    LEVEL_HIGH,
    LEVEL_CRITICAL
};

struct Error
{
    ErrCode error_code;
    ErrLevel error_severity;
    String module_name;
    String error_message;

    Error()
        : error_code{ErrCode::NONE}, error_severity{ErrLevel::LEVEL_NONE}, module_name{""}, error_message{""}
    {
    }

    Error(ErrCode code, ErrLevel level, const char *module_nm, const char *msg)
        : error_code{code}, error_severity{level}, module_name{module_nm}, error_message(msg)
    {
    }

    String get_formatted_error() const
    {
        String err_msg;
        err_msg += "[Module]: " + module_name;
        err_msg += " => " + error_message;
        return err_msg;
    }
};

class ErrorHandler
{
public:
    static void handle_error(const Error &error)
    {
        if (error.error_code != ErrCode::NONE)
        {
            Serial.printf("%s\n", error.get_formatted_error().c_str());
        }
    }
};

#endif /* ERROR_H */