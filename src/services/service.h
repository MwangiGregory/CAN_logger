#ifndef SERVICE_H
#define SERVICE_H

#include "../error.h"
class Service
{
public:
    virtual Error start_service() = 0;
    virtual Error stop_service() = 0;
};

#endif /* SERVICE_H */