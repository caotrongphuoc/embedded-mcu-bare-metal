#ifndef __ZW_GAME_TOMBSTONE_H__
#define __ZW_GAME_TOMBSTONE_H__

#include <stdio.h>

#include "fsm.h"
#include "port.h"
#include "message.h"
#include "timer.h"

#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "task_display.h"

/*---------------------------------------------------------------------------*/
/*  Constants                                                                */
/*---------------------------------------------------------------------------*/
#define TOMBSTONES_PER_LANE      (2)
#define NUM_TOMBSTONES           (10)
#define SIZE_BITMAP_TOMBSTONE_X  (8)
#define SIZE_BITMAP_TOMBSTONE_Y  (10)
#define TOMBSTONE_SPAWN_INTERVAL (35)
#define ZOMBIE_RISE_TICKS        (10)

/*---------------------------------------------------------------------------*/
/*  Data types                                                               */
/*---------------------------------------------------------------------------*/
typedef struct {
    uint8_t x;
    uint8_t lane;
    bool    active;
} zw_game_tombstone_t;

/*---------------------------------------------------------------------------*/
/*  Exported data                                                            */
/*---------------------------------------------------------------------------*/
extern zw_game_tombstone_t tombstones[NUM_TOMBSTONES];

/*---------------------------------------------------------------------------*/
/*  Task handler                                                             */
/*---------------------------------------------------------------------------*/
void zw_game_tombstone_handle(ak_msg_t* msg);

#endif /* __ZW_GAME_TOMBSTONE_H__ */
