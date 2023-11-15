#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "animation.h"
#include "entity.h"
#include "texture_controller.h"

class Player : public Entity{
public:
    Player(TextureController& texture_controller, int id);
    ~Player();

    void update_info(EntityInfo* info) override;
    void update(float dt) override;
    void render(SDL2pp::Renderer &renderer) override;

    uint16_t get_id() const override;

private:
    TextureController& texture_controller;
    Animation an;
    bool facingLeft;
    bool moving;
    bool jumping;
    bool rolling;

    int x;
    int y;
    int id;
    int health;
};

#endif // __PLAYER_H__