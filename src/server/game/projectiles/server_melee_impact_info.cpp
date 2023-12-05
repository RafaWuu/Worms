

#include "server_melee_impact_info.h"

MeleeSensorInfo::MeleeSensorInfo(const MeleeImpact& projectile): id(projectile.get_id()) {}

void MeleeSensorInfo::serialize_status(BaseProtocol& gp) { gp.send_1byte_number(id); }
void MeleeSensorInfo::serialize_scenario(BaseProtocol& gp) { gp.send_1byte_number(id); }
