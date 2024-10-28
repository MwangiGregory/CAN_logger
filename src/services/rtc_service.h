#ifndef RTC_SERVICE_H
#define RTC_SERVICE_H

#include "service.h"
#include "application.h"

enum class timestamp_type
{
    UNIX_TIME,
    DATETIME,
    DATE,
    TIME
};

class RTC_service : public Service
{
private:
    RTC_service() {}

public:
    Error start_service();
    Error stop_service();

    String get_timestamp(timestamp_type t = timestamp_type::DATETIME);
    Error set_rtc_time(const DateTime &new_time);
    Error set_rtc_time(const String &new_time);

    static RTC_service *get_service_instance();

private:
    RTC_DS3231 rtc;
};

#endif /* RTC_SERVICE_H */