#include "gps_service.h"

Error GPS_Service::start_service()
{
    gps_serial.begin(GPS_BAUD, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
    // TODO: gps takes a while to triangulate satellites
    // we could run some logic to retry successful connection
    // maybe query gps data until we get valid data
    return Error();
}

Error GPS_Service::stop_service()
{
    gps_serial.end();
    return Error();
}

String GPS_Service::get_location_str()
{
    // TODO: validate gps location data
    String output;
    output += String("Lat: ") + String(get_latitude());
    output += String(" ,");
    output += String("Long: ") + String(get_longitude());
    return output;
}

String GPS_Service::get_utc_timestamp()
{
    // TODO: validate gps datetime data
    String output;
    output += String(gps.date.year());
    output += "/";
    output += String(gps.date.month());
    output += "/";
    output += String(gps.date.day());
    output += ",";
    output += String(gps.time.hour());
    output += ":";
    output += String(gps.time.minute());
    output += ":";
    output += String(gps.time.second());
    return output;
}

// Has to be called periodically, maybe every round through the loop
Error GPS_Service::feed_gps()
{
    int bytes_count{};
    while (gps_serial.available() > 0)
        bytes_count += gps.encode(gps_serial.read());

    if (bytes_count <= 0)
        return Error(ErrCode::READ_ERROR, ErrLevel::LEVEL_MEDIUM, "feed_gps", "gps data read failed");

    return Error();
}

double GPS_Service::get_speed() { return gps.speed.kmph(); }

double GPS_Service::get_latitude() { return gps.location.lat(); }

double GPS_Service::get_longitude() { return gps.location.lng(); }

double GPS_Service::get_altitude() { return gps.altitude.meters(); }

GPS_Service *GPS_Service::get_service_instance()
{
    static GPS_Service gps_service;
    return &gps_service;
}
