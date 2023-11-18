#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include <memory>

#include <SDL2pp/SDL2pp.hh>

#include "animation.h"
#include "entity.h"
#include "texture_controller.h"
#include "weapons/weapon.h"
#include "weapons/weapon_factory.h"

class Player: public Entity {
public:
    Player(TextureController& texture_controller, int id);
    ~Player();

    void update_info(EntityInfo* info) override;
    void update(float dt) override;
    void render(SDL2pp::Renderer& renderer, SDL2pp::Rect& camera) override;

    uint16_t get_id() const override;

    AnimationState get_idle_texture();

private:
    TextureController& texture_controller;
    Animation an;
    bool facingLeft;
    bool moving;
    bool jumping;
    bool rolling;
    bool aiming;

    int x;
    int y;
    int id;
    int health;
    std::unique_ptr<Weapon> current_weapon;

    WeaponFactory weapon_factory;
};

#endif  // __PLAYER_H__