#ifndef _WEAPON_SELECTOR_H_
#define _WEAPON_SELECTOR_H_

#include <SDL2pp/SDL2pp.hh>
#include <memory>

#include "../../client_constants.h"

class WeaponSelector {
public:
    explicit WeaponSelector(SDL2pp::Renderer& renderer);

    void render(SDL2pp::Renderer& renderer);

    bool mouse_inside(int x, int y);

    int get_weapon_index(int x, int y);

private:
    std::unique_ptr<SDL2pp::Texture> texture;

    int height;
    int width;
};

#endif
