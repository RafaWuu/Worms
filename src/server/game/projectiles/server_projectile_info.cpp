

#include "server_projectile_info.h"

ProjectileInfo::ProjectileInfo(const Projectile& projectile): id(projectile.get_id()) {
    type = projectile.type;
    x = projectile.body->GetPosition().x;
    y = projectile.body->GetPosition().y;
    angle = projectile.body->GetAngle();
}
void ProjectileInfo::serialize_status(BaseProtocol& gp) {
    gp.send_1byte_number(id);
    gp.send_1byte_number(type);
    gp.send_4byte_float(x);
    gp.send_4byte_float(y);
    gp.send_4byte_float(angle);
}
void ProjectileInfo::serialize_scenario(BaseProtocol& gp) { gp.send_1byte_number(id); }
