

#include "server_worm_sensor_info.h"

#include "server_worm_sensor.h"
WormSensorInfo::WormSensorInfo(const WormSensor& sensor) { id = sensor.get_id(); }

void WormSensorInfo::serialize_scenario(BaseProtocol& gp) { gp.send_1byte_number(id); }
void WormSensorInfo::serialize_status(BaseProtocol& gp) { gp.send_1byte_number(id); }
