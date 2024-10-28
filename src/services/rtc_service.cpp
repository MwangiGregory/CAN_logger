#include "rtc_service.h"

Error RTC_service::start_service()
{
    if (Wire.setPins(RTC_SDA, RTC_SCL) == false)
        return Error(ErrCode::INIT_ERROR, ErrLevel::LEVEL_HIGH, "start_service", "rtc setPins failed");

    if (rtc.begin(&Wire) == false)
    {
        return Error(ErrCode::INIT_ERROR, ErrLevel::LEVEL_HIGH, "start_service", "rtc begin failed");
    }
    return Error();
}

Error RTC_service::stop_service()
{
    Wire.end();
    return Error();
}

String RTC_service::get_timestamp(timestamp_type t)
{
    DateTime time = rtc.now();
    String output;

    switch (t)
    {
    case timestamp_type::UNIX_TIME:
    {
        output = String(time.unixtime());
        break;
    }
    case timestamp_type::DATETIME:
    {
        output = time.timestamp(DateTime::TIMESTAMP_FULL);
        break;
    }
    case timestamp_type::DATE:
    {
        output = time.timestamp(DateTime::TIMESTAMP_DATE);
        break;
    }
    case timestamp_type::TIME:
    {
        output = time.timestamp(DateTime::TIMESTAMP_TIME);
        break;
    }
    default:
    {
        break;
    }
    }

    return output;
}

Error RTC_service::set_rtc_time(const DateTime &new_time)
{
    if (new_time.isValid() == false)
        return Error(ErrCode::WRITE_ERROR, ErrLevel::LEVEL_HIGH, "set_rtc_time", "Invalid DateTime");
    rtc.adjust(new_time);
    return Error();
}

Error RTC_service::set_rtc_time(const String &new_time)
{
    // TODO: find way to verify new_time is valid
    DateTime new_time_obj = DateTime(new_time.c_str());
    rtc.adjust(new_time_obj);
    return Error();
}

RTC_service *RTC_service::get_service_instance()
{
    static RTC_service rtc_service;
    return &rtc_service;
}
