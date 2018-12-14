

#ifndef r_garden_h_
#define r_garden_h_

//#define G4_ENABLE_CHIPMUNK
//#define G4_ENABLE_PARTICLES

#define GRDN_VERSION_MAJOR 0
#define GRDN_VERSION_MINOR 0
#define GRDN_VERSION_PATCH 1
#define RUMINANT_GRDN_PRESENT

#include "stdio.h"
#include "stdlib.h"
#include "src/util/grdn_log.h"

int		    grdn_check_version_match(const char* str);
int		    grdn_check_compat_match(const char* str);
char*		    grdn_get_version_string(void);
char*		    grdn_get_compat_string(void);


static inline char* grdn_get_compat_string_header(void)
{
	char* buf = (char*)calloc(256, sizeof(char));
	sprintf(buf, "%d.%d", GRDN_VERSION_MAJOR, GRDN_VERSION_MINOR);
	return buf;
}

static inline char* grdn_get_version_string_header(void)
{
	char* buf = (char*)calloc(256, sizeof(char));
	sprintf(buf, "%d.%d.%d", GRDN_VERSION_MAJOR, GRDN_VERSION_MINOR,
		GRDN_VERSION_PATCH);
	return buf;
}


#include "src/ent/g_entity.h"
#include "src/ent/g_entsys.h"
#include "src/ent/g_think.h"
#include "src/env/g_world.h"
#include "src/ent/g_factory.h"

#include "src/comp/g_body.h"
#include "src/comp/g_dac.h"

#include "src/story/g_story.h"
#include "src/story/grdn_dialogtree.h"

#include "src/particle/g_attractor.h"
#include "src/particle/g_particle.h"
#include "src/particle/g_particle_presets.h"
#include "src/particle/g_particle_system.h"
#include "src/physics/grdn_physics.h"
#include "src/physics/grdn_physics_cloth.h"
#include "src/physics/grdn_physics_space.h"

// todo deprecate the old one (below)
#include "src/particle/g_particlesystem.h"

#include "src/env/g_map.h"
#include "src/env/g_area.h"
#include "src/env/g_player.h"
#include "src/env/g_clock.h"
#include "src/env/g_dialog.h"
#include "src/env/g_vecfield.h"

//#include "src/ent/g_factory.h"

#include "src/render/g_render.h"
#include "src/render/g_render_wsh.h"

#include "src/scene/g_background.h"
#include "src/scene/g_camera.h"
#include "src/scene/g_light.h"
#include "src/scene/g_textseq.h"
#include "src/scene/g_weather.h"

#include "src/core/g_game.h"

int  grdn_init(void);
void grdn_deinit(void);

#endif
