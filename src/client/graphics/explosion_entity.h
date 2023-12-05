#ifndef CLIENT_PROJECTILE_ENTITY_H
#define CLIENT_PROJECTILE_ENTITY_H

#include "animation.h"
#include "entity.h"
#include "camera.h"

class ExplosionEntity: public Entity {
public:
    explicit ExplosionEntity(TextureController& texture_controller, uint8_t type, float radius);
    ~ExplosionEntity();

    void update_info(EntityInfo* info, SoundController& sound_controller) override;
    void update(float dt) override;
    void render(SDL2pp::Renderer& renderer, Camera& camera) override;

private:
    TextureController& texture_controller;

    Animation circle;
    Animation elipse;

    uint8_t type;
    int id;
    float radius;
    Configuration& config;
    int x;
    int y;

    int frames_rendered;

    bool just_exploded;
};
#endif  
