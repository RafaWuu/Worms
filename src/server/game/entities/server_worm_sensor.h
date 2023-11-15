//
// Created by xguss on 05/11/23.
//

#ifndef WORMS_SERVER_WORM_SENSOR_H
#define WORMS_SERVER_WORM_SENSOR_H

#include "server_gameobject.h"
#include "server_worm.h"

class WormSensor: public GameObject {
private:
    Worm* worm;

public:
    explicit WormSensor(Worm* worm);

    ObjectType get_id() const override;

    std::unique_ptr<GameObjectInfo> get_status() const override;

    void handle_begin_floor_contact(GameObject* other);

    void handle_end_floor_contact(GameObject* pObject);

};
#endif  // WORMS_SERVER_WORM_SENSOR_H
