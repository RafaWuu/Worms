#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <memory>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "weapons/weapon.h"
#include "weapons/weapon_factory.h"

#include "animation.h"
#include "crosshair.h"
#include "entity.h"
#include "texture_controller.h"

class Player: public Entity {
public:
    Player(TextureController& texture_controller, int id);
    ~Player();

    void update_info(EntityInfo* info) override;

    void update(float dt) override;

    void render(SDL2pp::Renderer& renderer, SDL2pp::Rect& camera) override;

    uint16_t get_id() const override;

    AnimationState get_idle_texture();

    void render_crosshair(SDL2pp::Renderer& renderer);
    void set_color(SDL2pp::Color color);

private:
    TextureController& texture_controller;
    Animation an;

    bool facingLeft;
    bool moving;
    bool jumping;
    bool rolling;
    bool aiming;
    bool falling;
    bool idle;
    bool dead;
    float aim_angle;

    int x;
    int y;
    uint16_t height;
    uint16_t width;
    int id;
    int health;

    std::unique_ptr<Weapon> current_weapon;
    WeaponFactory weapon_factory;
    SDL2pp::Color color;
    Crosshair crosshair;
    Configuration& config;
};

#endif  // __PLAYER_H__