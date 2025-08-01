#include "../MexTK/mex.h"
#include "events.h"

typedef struct LCancelData LCancelData;
typedef struct LCancelAssets LCancelAssets;

struct LCancelData
{
    EventDesc *event_desc;
    LCancelAssets *lcancel_assets;
    GOBJ *barrel_gobj;
    Vec3 barrel_lastpos;
    bool is_fail;      // status of the last l-cancel
    bool is_fastfall;  // bool used to detect fastfall frame
    u8 fastfall_frame; // frame the player fastfell on
    u8 current_l_input_timing;      // number of frames an L was input before the current aerial landing
    bool is_current_aerial_counted; // whether or not the current aerial has already been tracked as a success or failure
    struct
    {
        GOBJ *gobj;
        u16 lcl_success;
        u16 lcl_total;
        Text *text_time;
        Text *text_air;
        Text *text_scs;
        int canvas;
        float arrow_base_x; // starting X position of arrow
        float arrow_prevpos;
        float arrow_nextpos;
        int arrow_timer;
    } hud;
    struct
    {
        u8 shield_isdisp;   // whether tip has been shown to the player
        u8 shield_num;      // number of times condition has been met
        u8 hitbox_active;   // whether or not the last aerial used had a hitbox active
        u8 hitbox_isdisp;   // whether tip has been shown to the player
        u8 hitbox_num;      // number of times condition has been met
        u8 fastfall_active; // whether or not the last aerial used had a hitbox active
        u8 fastfall_isdisp; // whether tip has been shown to the player
        u8 fastfall_num;    // number of times condition has been met
        u8 late_isdisp;     // whether tip has been shown to the player
        u8 late_num;        // number of times condition has been met
    } tip;
};

struct LCancelAssets
{
    JOBJDesc *hud;
    void **hudmatanim; // pointer to array
};

#define LCLTEXT_SCALE 4.2
#define LCLARROW_ANIMFRAMES 4
#define LCLARROW_JOBJ 7
#define LCLARROW_OFFSET 0.365

// Maximum number of frames before a miss is considered "No Press", using zero-based indexing.
#define MAX_L_PRESS_TIMING 29

void Tips_Toggle(GOBJ *menu_gobj, int value);
void Tips_Think(LCancelData *event_data, FighterData *hmn_data);
void LCancel_Think(LCancelData *event_data, FighterData *hmn_data);
void LCancel_HUDCamThink(GOBJ *gobj);
void LCancel_Init(LCancelData *event_data);
void Barrel_Think(LCancelData *event_data);
void Barrel_Toggle(GOBJ *menu_gobj, int value);
GOBJ *Barrel_Spawn(int pos_kind);
int Barrel_OnHurt(GOBJ *barrel_gobj);
int Barrel_OnDestroy(GOBJ *barrel_gobj);
void Barrel_Null(void);
void Event_Exit(GOBJ *menu);
bool IsAerialLandingState(int state_id);
bool IsEdgeCancelState(int state_id);
bool IsAutoCancelLanding(FighterData *hmn_data);
