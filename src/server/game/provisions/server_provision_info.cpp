

#include "server_provision_info.h"

ProvisionInfo::ProvisionInfo(const Provision& provision) {
    id = provision.get_id();
    x = provision.body->GetPosition().x;
    y = provision.body->GetPosition().y;
}

void ProvisionInfo::serialize_scenario(BaseProtocol& bp) { bp.send_1byte_number(id); }

void ProvisionInfo::serialize_status(BaseProtocol& bp) {
    bp.send_1byte_number(id);
    bp.send_4byte_float(x);
    bp.send_4byte_float(y);
}
