#include "hud.h"

Hud::Hud(SDL2pp::Renderer& renderer, std::map<uint16_t,uint16_t>& worms_distribution):
    renderer(renderer),
    worms_distribution(worms_distribution),
    ammo(0),
    time(0){
        // por ahi hacer un map de {client_id:worm/player class}
        // for (auto pair : worms_distribution)
        // {
        //    hp_map[pair.second][pair.first] = 0;
        // }
    }

void Hud::update_hp(int worm_id, int hp ){
    
}
void Hud::update_time(int time){
    time = time;
}
void Hud::update_ammo( int worm_id, int ammo){
    if (worm_id == current_worm){
        ammo = ammo;
    }
}
void Hud::update_current_worm (int worm_id){
    worm_id = current_worm;
}
void Hud::render_hp(SDL2pp::Renderer& renderer){
    //client_hp --> client_id:{worm_id:worm_hp,..,...}
    int i = 0;
    for ( auto pair : hp_map){
        int hp = 0;
        for ( auto p: pair.second){
            hp += p.second;
        }
        SDL2pp::Font font("assets/Vera.ttf", 12);
        std::string text = "Client " + std::to_string(pair.first) + std::to_string(hp);
	    SDL2pp::Texture hp_sprite(
		renderer,
		font.RenderText_Blended(text, SDL2pp::Color{0, 255, 0, 255}));

	    renderer.Copy(hp_sprite,
                     SDL2pp::NullOpt,
                    SDL2pp::Rect(0,
                                hp_sprite.GetHeight()*i,
                                hp_sprite.GetWidth(), 
                                hp_sprite.GetHeight()));
        i++;
    }
    
}

void Hud::render_ammo(SDL2pp::Renderer& renderer){
        SDL2pp::Font font("assets/Vera.ttf", 12);
        std::string text = "Ammo: "  + std::to_string(0);
	    SDL2pp::Texture ammo_sprite(
		renderer,
		font.RenderText_Blended(text, SDL2pp::Color{255, 0, 0, 255}));

	    renderer.Copy(ammo_sprite,
                     SDL2pp::NullOpt,
                    SDL2pp::Rect(0,
                                0,
                                ammo_sprite.GetWidth(), 
                                ammo_sprite.GetHeight()));
}

void Hud::render_timer(SDL2pp::Renderer& renderer){

}

void Hud::render(SDL2pp::Renderer& renderer){
//    render_hp();
   render_ammo(renderer);
// render_timer();
}

Hud::~Hud(){}
