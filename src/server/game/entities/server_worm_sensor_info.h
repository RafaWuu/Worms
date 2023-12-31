

#ifndef WORMS_SERVER_WORM_SENSOR_INFO_H
#define WORMS_SERVER_WORM_SENSOR_INFO_H

#include "server_gameobject_info.h"
#include "server_worm_sensor.h"
class WormSensorInfo: public GameObjectInfo {
private:
    ObjectType id;

public:
    explicit WormSensorInfo(const WormSensor& sensor);
    void serialize_scenario(BaseProtocol& gp) override;
    void serialize_status(BaseProtocol& gp) override;
};

#endif  // WORMS_SERVER_WORM_SENSOR_INFO_H
