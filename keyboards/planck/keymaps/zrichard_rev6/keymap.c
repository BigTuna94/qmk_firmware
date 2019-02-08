/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "muse.h"
#include "action_layer.h"
#include "eeconfig.h"

/*
#include "audio.h"
#include "song_list.h"

#ifdef AUDIO_ENABLE
void matrix_init_user(void)
{
    set_voice(default_voice);
    startup_user();
    println("Matrix Init");
}

void startup_user()
{
    //_delay_ms(10); // gets rid of tick
    PLAY_SONG(tone_my_startup);
}

void shutdown_user()
{
    PLAY_SONG(tone_my_goodbye);
    //_delay_ms(2000);
    stop_all_notes();
}

void audio_on_user(void)
{
  PLAY_SONG(tone_audio_on);
}

void music_on_user(void)
{
  PLAY_SONG(tone_music_on);
}

void music_scale_user(void)
{
  PLAY_SONG(music_scale);
}

#endif // AUDIO_ENABLE 
*/


extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _FUNCTION,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  FUNCTION,
  MINE,
  TIMBRE_1,
  TIMBRE_2,
  TIMBRE_3,
  TIMBRE_4,
  TEMPO_U,
  TEMPO_D,
  TONE_DEFAULT,
  MUSIC_TOGGLE,
  AUDIO_TOGGLE,
  INC_VOICE,
  DEC_VOICE,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 *
 *  .-----------------------------------------------------------------------------------------------------------.
 *  | ESC    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | BACKSP |
 *  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *  | TAB    | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | '      |
 *  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *  | LSHIFT | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | UP     | SH/ENT |
 *  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 *  | LCTRL  |  FN    | LALT   | LWIN   | LOWER  | SPACE  | SPACE  | UPPER  |  MENU  | LEFT   | DOWN   | RIGHT  |
 *  '-----------------------------------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
   KC_ESC , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC  ,
   KC_TAB , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT  ,
   KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_UP  , KC_SFTENT,
   KC_LCTL, FUNCTION,KC_LALT, KC_LGUI, LOWER,   KC_SPC , KC_SPC , RAISE,   KC_APP , KC_LEFT, KC_DOWN, KC_RGHT 
),

/* Lower
 * .-----------------------------------------------------------------------------------------------------------.
 * | ______ | $      | {      | [      | (      | %      | #      | )      | ]      | }      | @      | PG UP  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | ______ | ^      | *      | +      | -      | /      | \      | _      | '      | "      | `      | PG DN  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | ______ | |      | &      | !      | ~      | ;      | :      | =      | <      | >      | ?      | HOME   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | ______ | ______ | ______ | ______ | ______ | ______ | ______ | UPPER  | ______ | ______ | ______ | END    |
 * '-----------------------------------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
   _______, KC_DLR , KC_LCBR, KC_LBRC, KC_LPRN, KC_PERC, KC_HASH, KC_RPRN, KC_RBRC, KC_RCBR, KC_AT  , KC_PGUP ,
   _______, KC_CIRC, KC_ASTR, KC_PLUS, KC_MINS, KC_SLSH, KC_BSLS, KC_UNDS, KC_QUOT, KC_DQT , KC_GRV , KC_PGDN ,
   _______, KC_PIPE, KC_AMPR, KC_EXLM, KC_TILD, KC_SCLN, KC_COLN, KC_EQL , KC_LT  , KC_GT  , KC_QUES, KC_HOME ,
   _______, _______, _______, _______, _______, _______, _______, RAISE,   _______, _______, _______, KC_END  
),

/* Raise
 * .-----------------------------------------------------------------------------------------------------------.
 * | PRINT  | F1     | F2     | F3     | F4     | NUM LK | KP /   | KP 7   | KP 8   | KP 9   | KP -   | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | PAUSE  | F5     | F6     | F7     | F8     | SCR LK | KP *   | KP 4   | KP 5   | KP 6   | KP +   | HOME   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | ______ | F9     | F10    | F11    | F12    | PAUSE  | KP 0   | KP 1   | KP 2   | KP 3   | KP ENT | END    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | ______ | ______ | ______ | ______ | LOWER  | KP 0   | KP 0   | ______ | RALT   | KP 0   | KP ENT | RTCTRL |
 * '-----------------------------------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(  
   KC_PSCR, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_NLCK, KC_PSLS, KC_7, KC_8, KC_9,   KC_MINS, KC_DEL  ,
   KC_PAUS, KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_SLCK, KC_PAST, KC_4, KC_5, KC_6,   KC_PLUS, KC_HOME ,
   _______, KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_PAUS, KC_KP_0, KC_1, KC_2, KC_3,   KC_ENT , KC_END  ,
   _______, _______, _______, _______, LOWER,   KC_KP_0, KC_KP_0, _______, KC_0, KC_DOT, KC_ENT , KC_RCTL 
),

/* Function 
 * .-----------------------------------------------------------------------------------------------------------.
 * | XXXXXX | F13    | F14    | F15    | F16    | NUM LK | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | XXXXXX | F17    | F18    | F19    | F20    | SCR LK | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | ______ | F21    | F22    | F23    | F24    | CAP LK | XXXXXX | XXXXXX | XXXXXX | XXXXXX | VOL UP | MUTE   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | ______ | ______ | FN     | ______ | ______ | PLAY   | PLAY   | ______ | ______ | PREV   | VOL DN | NEXT   |
 * '-----------------------------------------------------------------------------------------------------------'
 */
[_FUNCTION] = LAYOUT_planck_grid(
   XXXXXXX, KC_F13 , KC_F14 , KC_F15 , KC_F16 , KC_NLCK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX ,
   XXXXXXX, KC_F17 , KC_F18 , KC_F19 , KC_F20 , KC_SLCK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX ,
   _______, KC_F21 , KC_F22 , KC_F23 , KC_F24 , KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU, KC_MUTE ,
   _______, _______, FUNCTION, _______, _______, KC_MPLY, KC_MPLY, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT 
),

/* Adjust (Lower + Raise)
 * .-----------------------------------------------------------------------------------------------------------.
 * | XXXXXX | HELP 1 | HELP 2 | HELP 3 | HELP 4 | HELP 5 | HELP 6 | HELP 7 | HELP 8 | HELP 9 | MUSIC  | AUDIO  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | XXXXXX | BRTOG  | BRSPD+ | BRSPD- | BRDFLT | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | XXXXXX | QWERTY | XXXXXX | XXXXXX | BACKLT | RESET  | XXXXXX | MOUSE  | XXXXXX | XXXXXX | VOICE+ | MACRO  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | XXXXXX | XXXXXX | XXXXXX | XXXXXX | LOWER  | XXXXXX | XXXXXX | UPPER  | XXXXXX | TEMPO- | VOICE- | TEMPO+ |
 * '-----------------------------------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MU_MOD , MU_TOG , AU_TOG  ,
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX ,
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MUV_IN , MINE,
   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LOWER,   XXXXXXX, XXXXXXX, RAISE,   XXXXXXX, TEMPO_D, MUV_DE , TEMPO_U 
)

};

#ifdef AUDIO_ENABLE

float tone_my_startup[][2] = SONG(QWERTY_SOUND);
float tone_my_goodbye[][2] = SONG(QWERTY_SOUND);

float tone_audio_on[][2]   = SONG(CLOSE_ENCOUNTERS_5_NOTE);
float tone_music_on[][2]   = SONG(DOE_A_DEER);
float tone_caps_on[][2]    = SONG(CAPS_LOCK_ON_SOUND);
float tone_caps_off[][2]   = SONG(CAPS_LOCK_OFF_SOUND);
float tone_numlk_on[][2]   = SONG(NUM_LOCK_ON_SOUND);
float tone_numlk_off[][2]  = SONG(NUM_LOCK_OFF_SOUND);
float tone_scroll_on[][2]  = SONG(SCROLL_LOCK_ON_SOUND);
float tone_scroll_off[][2] = SONG(SCROLL_LOCK_OFF_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);

#endif /* AUDIO_ENABLE */

void persistant_default_layer_set(uint16_t default_layer)
{
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_MODS_ONESHOT(MOD_RSFT),
};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

//const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode)
    {
        case FUNCTION:
            if (record->event.pressed)
            {
                layer_on(_FUNCTION);
            }
            else
            {
                layer_off(_FUNCTION);
            }
            break;

        case MINE:
          if(record->event.pressed)
          {
            return MACRO( I(03), T(R), T(O), T(O), T(T), W(10), T(TAB), W(10), T(T), T(O), T(O), T(R), T(ENTER), END );
          }
          break;
/*
#ifdef AUDIO_ENABLE

        case TIMBRE_1:
            if (record->event.pressed) set_timbre(TIMBRE_12);
            break;

        case TIMBRE_2:
            if (record->event.pressed) set_timbre(TIMBRE_25);
            break;

        case TIMBRE_3:
            if (record->event.pressed) set_timbre(TIMBRE_50);
            break;

        case TIMBRE_4:
            if (record->event.pressed) set_timbre(TIMBRE_75);
            break;

        case TEMPO_U:
            if (record->event.pressed) increase_tempo(10);
            break;

        case TEMPO_D:
            if (record->event.pressed) decrease_tempo(10);
            break;

        case TONE_DEFAULT:
            if (record->event.pressed)
            {
                set_timbre(TIMBRE_DEFAULT);
                set_tempo(TEMPO_DEFAULT);
            }
            break;

#endif // AUDIO_ENABLE 
*/
        default:
            return true;

    }

    return false;
}

