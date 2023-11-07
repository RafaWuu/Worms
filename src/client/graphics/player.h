#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <SDL2pp/SDL2pp.hh>
#include "textureController.h"
#include "animation.h"
#include "../game/worm.h"
#include <vector>

class Player {
public:
    Player(TextureController& texture_controller, int id);
    ~Player();
    void update(float dt);
    void render(SDL2pp::Renderer &renderer);
    void moveRigth();
    void moveLeft();
    void stopMoving();
    int get_id() const;
    void update_info(Worm& worm);

private:
    TextureController& texture_controller;
    Animation an;
    bool facingLeft;
    bool moving;
    int x;
    int y;
    int id;
    int health;
};

#endif // __PLAYER_H__