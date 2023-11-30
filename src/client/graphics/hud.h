#ifndef __DESKTOP_WORMS_SRC_CLIENT_GRAPHICS_HUD_H_
#define __DESKTOP_WORMS_SRC_CLIENT_GRAPHICS_HUD_H_

#include <string>
#include <map>
#include <SDL2pp/SDL2pp.hh>

class Hud {
	private:
		SDL2pp::Renderer& renderer;
        std::map<uint16_t,uint16_t>& worms_distribution;
        std::map<int,std::map<int,int>> hp_map;
		int current_worm;
		int time;
		int ammo;
		
        void render_ammo(SDL2pp::Renderer& renderer);
        void render_hp(SDL2pp::Renderer& renderer);
        void render_timer(SDL2pp::Renderer& renderer);

	public:

		Hud(SDL2pp::Renderer& renderer, std::map<uint16_t,uint16_t>& client_worm);
		void update_hp(int worm_id, int hp );
		void update_time(int time);
		void update_current_worm (int worm_id);
		void update_ammo(int worm_id, int ammo);
		void render(SDL2pp::Renderer& renderer);
		~Hud();
};


#endif // __DESKTOP_WORMS_SRC_CLIENT_GRAPHICS_HUD_H_
