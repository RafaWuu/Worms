#ifndef __DESKTOP_WORMS_SRC_CLIENT_GRAPHICS_HUD_H_
#define __DESKTOP_WORMS_SRC_CLIENT_GRAPHICS_HUD_H_

#include <string>
#include <map>
#include <SDL2pp/SDL2pp.hh>

class Hud {
	private:
		SDL2pp::Renderer& renderer;
        std::map<uint16_t,uint16_t> worms_distribution;
        std::map<int,std::map<int,int>> hp_map;
		int client_id;
		int time;
		int ammo;
		int offset;
        void render_ammo();
        void render_hp();
        void render_timer();

	public:

		Hud(SDL2pp::Renderer& renderer, std::map<uint16_t,uint16_t> worms_distribution, int client_id);
		void update_hp(int worm_id, int hp);
		void update_time(float time);
		void update_ammo(int worm_id, int ammo);
		void render();
		~Hud();
};


#endif // __DESKTOP_WORMS_SRC_CLIENT_GRAPHICS_HUD_H_
