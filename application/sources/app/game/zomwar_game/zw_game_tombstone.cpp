#include "zw_game_tombstone.h"
#include "zw_game_zombie.h"
#include "zw_game_car.h"
#include "scr_zomwar_game.h"

/*---------------------------------------------------------------------------*/
/*  Internal data                                                            */
/*---------------------------------------------------------------------------*/
zw_game_tombstone_t tombstones[NUM_TOMBSTONES];

static uint8_t tombstone_spawn_timer = 0;

/*---------------------------------------------------------------------------*/
/*  Internal helpers                                                         */
/*---------------------------------------------------------------------------*/
static void tombstone_clear(uint8_t i) {
    tombstones[i].x      = 0;
    tombstones[i].lane   = 0;
    tombstones[i].active = false;
}

/*---------------------------------------------------------------------------*/
/*  Signal handlers                                                          */
/*---------------------------------------------------------------------------*/
static void zw_game_tombstone_setup(void) {
    tombstone_spawn_timer = TOMBSTONE_SPAWN_INTERVAL;

    for (uint8_t l = 0; l < NUM_LANES; l++) {
        tombstones[l].x      = (uint8_t)(rand() % 20 + 65);
        tombstones[l].lane   = l;
        tombstones[l].active = (bool)((settingsetup.tombstone_lane_1 >> l) & 1);

        tombstones[l + NUM_LANES].x      = (uint8_t)(rand() % 20 + 90);
        tombstones[l + NUM_LANES].lane   = l;
        tombstones[l + NUM_LANES].active = (bool)((settingsetup.tombstone_lane_2 >> l) & 1);
    }
}

static void zw_game_tombstone_update(void) {
    if (tombstone_spawn_timer > 0) {
        tombstone_spawn_timer--;
        return;
    }

    tombstone_spawn_timer = TOMBSTONE_SPAWN_INTERVAL;

    uint8_t tidx = (uint8_t)(rand() % NUM_TOMBSTONES);
    if (tombstones[tidx].active) {
        task_post_pure_msg(ZW_GAME_TOMBSTONE_ID, ZW_GAME_TOMBSTONE_SPAWN);
    }
}

static void zw_game_tombstone_spawn(void) {
    uint8_t tidx = (uint8_t)(rand() % NUM_TOMBSTONES);
    if (!tombstones[tidx].active) return;

    for (uint8_t i = 0; i < NUM_ZOMBIES; i++) {
        if (zombie[i].visible != WHITE) {
            spawn_zombie_from_tombstone(i, tidx);
            return;
        }
    }
}

static void zw_game_tombstone_reset(void) {
    tombstone_spawn_timer = 0;

    for (uint8_t i = 0; i < NUM_TOMBSTONES; i++) {
        tombstone_clear(i);
    }
}

/*---------------------------------------------------------------------------*/
/*  Task handler                                                             */
/*---------------------------------------------------------------------------*/
void zw_game_tombstone_handle(ak_msg_t* msg) {
    switch (msg->sig) {
    case ZW_GAME_TOMBSTONE_SETUP: {
        APP_DBG_SIG("ZW_GAME_TOMBSTONE_SETUP\n");
        zw_game_tombstone_setup();
    }
        break;

    case ZW_GAME_TOMBSTONE_UPDATE: {
        APP_DBG_SIG("ZW_GAME_TOMBSTONE_UPDATE\n");
        zw_game_tombstone_update();
    }
        break;

    case ZW_GAME_TOMBSTONE_SPAWN: {
        APP_DBG_SIG("ZW_GAME_TOMBSTONE_SPAWN\n");
        zw_game_tombstone_spawn();
    }
        break;

    case ZW_GAME_TOMBSTONE_RESET: {
        APP_DBG_SIG("ZW_GAME_TOMBSTONE_RESET\n");
        zw_game_tombstone_reset();
    }
        break;

    default:
        break;
    }
}
