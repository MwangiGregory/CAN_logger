#ifndef GPS_SERVICE_H
#define GPS_SERVICE_H

#include "application.h"
#include "service.h"

class GPS_Service : public Service
{
private:
    GPS_Service() {}

    double get_latitude();
    double get_longitude();
    double get_speed();
    double get_altitude();

public:
    Error start_service();
    Error stop_service();
    Error feed_gps();

    String get_location_str();
    String get_utc_timestamp();

    static GPS_Service *get_service_instance();

private:
    TinyGPSPlus gps;
    HardwareSerial gps_serial{GPS_SERIAL_DEVICE};
};

#endif /* GPS_SERVICE_H */