//
// Created by xguss on 14/11/23.
//

#include "server_worm_sensor_info.h"

#include "server_worm_sensor.h"
WormSensorInfo::WormSensorInfo(const WormSensor& sensor) : sensor(sensor) {}

void WormSensorInfo::serialize_scenario(ServerProtocol& gp) {
    gp.send_1byte_number(sensor.get_id());

}
void WormSensorInfo::serialize_status(ServerProtocol& gp) {
    gp.send_1byte_number(sensor.get_id());
}
