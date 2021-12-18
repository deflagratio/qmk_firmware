 /* Copyright 2020 Naoki Katahira
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
#include <stdio.h>

//extern uint8_t is_master;

enum layer_number {
  _WORKMAN = 0,
  _QWERTY,
  _NAV,
  _NUM,
};

//define layer key names
#define RAISE MO(_NAV)
#define LOWER MO(_NUM)


//Tap Dance Declarations
enum {
  TD_SCREEN_CAP = 0,
  TD_QWERTY,
  TD_WORK,
  TD_BRAC_OP,
  TD_BRAC_CL
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for snipping tool, twice for Print Screen
  [TD_SCREEN_CAP]  = ACTION_TAP_DANCE_DOUBLE(LSG(KC_S), KC_PSCR),
// ESCAPE ON TAP, CHANGE DEFAULT LAYER TO QWERTY
  [TD_QWERTY]  = ACTION_TAP_DANCE_DUAL_ROLE(KC_ESC, _QWERTY),
  [TD_WORK]  = ACTION_TAP_DANCE_DUAL_ROLE(KC_ESC, _WORKMAN),
  // Regular on tap. shifted command on double tap.
  [TD_BRAC_OP]  = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, S(KC_LBRC)),
  [TD_BRAC_CL]  = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, S(KC_RBRC))
};

//define macro keyname. Add MacroName, and then define actions in bool below.
enum custom_keycodes {
  SPOILER = SAFE_RANGE,
  SUM,
};
//define macro actions. Can Copy from Case to Break and modify as needed
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SPOILER:
    if (record->event.pressed) {
        //when keycode SPOILER is pressed
        SEND_STRING("||");
      } else {
        //when keycode is released
      }
      break;
  //begin second macro, Sum formula
   case SUM:
    if (record->event.pressed) {
        //when keycode SUM is pressed
        SEND_STRING("=sum(");
      } else {
        //when keycode is released
      }
      break;
}
return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* WORKMAN
 * ,---------------------------------------------.                    ,---------------------------------------------.
 * | ESC/LAYOUT|   1 |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |TOGGLE NAV|
 * |----------+------+------+------+------+------|                    |------+------+------+------+------+----------|
 * | Tab      |   Q  |   D  |   R  |   W  |   B  |                    |   J  |   F  |   U  |   P  |   ;  |  -       |
 * |----------+------+------+------+------+------|                    |------+------+------+------+------+----------|
 * |LCTRL     |   A  |   S  |   H  |   T  |   G  |-------.    ,-------|   Y  |   N  |   E  |   O  |   I  |  '       |
 * |----------+------+------+------+------+------|ALTTAB |    |CRTLTAB|------+------+------+------+------+----------|
 * |LShift/cap|   Z  |   X  |   M  |   C  |   C  |-------|    |-------|   K  |   L  |   ,  |   .  |   /  |RIGHTCLICK|
 * `--------------------------------------------/       /     \      \-----------------------------------------'
 *           |SCREENCAP/ | DELETE| SPACE/    | /RAISE/ /       \lOWER \  |SPACE  | BACKSPACE |NUMLOCK/|
 *           |PRINTSCREEN|       |  SHIFT    |/ ENTER /         \ENTER \ | SHIFT |           |  WIN   |
 *           `-----------------------------''-------'           '------''-----------------------------'
 */

 [_WORKMAN] = LAYOUT(
  TD_QWERTY  , KC_1, KC_2,  KC_3,  KC_4,    KC_5,                              KC_6,     KC_7,    KC_8,    KC_9,    KC_0,    TG(RAISE),
  KC_TAB        , KC_Q, KC_D,  KC_R,  KC_W,    KC_B,                              KC_J,     KC_F,    KC_U,    KC_P,    KC_SCLN, KC_MINS,
  KC_LCTRL      , KC_A, KC_S,  KC_H,  KC_T,    KC_G,                              KC_Y,     KC_N,    KC_E,    KC_O,    KC_I,    KC_QUOT,
  SFT_T(KC_CAPS), KC_Z, KC_X,  KC_M,  KC_C,    KC_V, LALT(KC_TAB),     C(KC_TAB), KC_K,     KC_L,    KC_COMM, KC_DOT,  KC_SLSH, KC_BTN1,
       TD(TD_SCREEN_CAP), KC_DEL, SFT_T(KC_SPC), LT(RAISE,KC_ENT),        LT(LOWER,KC_ENT),  SFT_T(KC_SPC),  KC_BSPC, LGUI_T(KC_NLCK)
),
/* QWERTY
* ,-----------------------------------------------.                    ,---------------------------------------------.
 * | ESC/LAYOUT|   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |TOGGLE NAV|
* |------------+------+------+------+------+------|                    |------+------+------+------+------+----------|
* | TAB        |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -       |
* |------------+------+------+------+------+------|                    |------+------+------+------+------+----------|
* |LCTRL       |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '       |
 * |-----------+------+------+------+------+------|ALTTAB |    |CRTLTAB|------+------+------+------+------+----------|
* |Sft/(       |   Z  |   X  |   C  |   V  |   B  |-------.    ,-------|   N  |   M  |   ,  |   .  |   /  |RIGHTCLICK|
* `----------------------------------------------/       /     \      \----------------------------------------------'
*             |SCREENCAP/ | DELETE| SPACE/    | /RAISE/ /       \lOWER \ |SPACE  | BACKSPACE |NUMLOCK/|
*            |PRINTSCREEN|        |  SHIFT    |/ ENTER /         \ENTER \| SHIFT |           | WIN    |
*           `--------------------------------''-------'          '------''----------------------------'
*/
[_QWERTY] = LAYOUT(
   TD_WORK,     KC_1, KC_2,  KC_3,  KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    TG(RAISE),
   KC_TAB,         KC_Q, KC_W,  KC_E,  KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
   KC_LCTRL,       KC_A, KC_S,  KC_D,  KC_F,    KC_G,                          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
   SFT_T(KC_CAPS), KC_Z, KC_X,  KC_C,  KC_V,    KC_B, LALT(KC_TAB), C(KC_TAB), KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_BTN1,
     TD(TD_SCREEN_CAP), KC_DEL, SFT_T(KC_SPC), LT(RAISE,KC_ENT),        LT(LOWER,KC_ENT),  SFT_T(KC_SPC),  KC_BSPC, LGUI_T(KC_NLCK)
 ),
/* NAV
 * ,-----------------------------------------------.                    ,----------------------------------------------------------.
 * |CTRL,ALT,DEL|      |      |      |      |      |                    |          |         |          |          |      |        |
 * |------------+------+------+------+------+------|                    |----------+---------+----------+----------+------+--------|
 * | TRAN       | TRAN | HOME |  UP  |  END |  WUP |                    |          |  WR     |  MSU     | WL       | WU   |        |
 * |------------+------+------+------+------+------|                    |----------+---------+----------+----------+------+--------|
 * | TRAN       | TRAN | LEFT | DOWN | RIGHT| WDOWN|-------.    ,-------| CTL SPACE| MSL     | MSD      | MSR      | WD   |        |
 * |------------+------+------+------+------+------|   [   |    |    ]  |----------+---------+----------+----------+------+--------|
 * | TRAN       |      |      |      |      |      |-------|    |-------|   CRTL   |MOUSE A0 | MOUSE A1 | MOUSE A2 | TRAN | MOUSE1 |
 * `----------------------------------------------/       /     \      \----------------------------------------------------------'
 *                    |MOUSE3 | MOUSE2 | MOUSE1  | TRAN  /       \ TRAN \  |LShift| CRTL+ |DELETE |
 *                    |       |        |        |/      /         \      \ |      | LShift|       |
 *                    `-----------------------''-------'           '------''----------------------'
 */

[_NAV] = LAYOUT(
  LCA(KC_DEL), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  KC_TRNS,     XXXXXXX, KC_HOME,   KC_UP,  KC_END, KC_WH_U,                       XXXXXXX, KC_WH_L, KC_MS_U, KC_WH_R, KC_WH_U, XXXXXXX,
  KC_TRNS,     XXXXXXX, KC_LEFT, KC_DOWN,KC_RIGHT, KC_WH_D,                     C(KC_SPC), KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, XXXXXXX,
  KC_TRNS,     C(KC_Z), C(KC_X), C(KC_C), C(KC_V), C(KC_F), KC_TRNS,    KC_TRNS, KC_LCTRL, KC_ACL0, KC_ACL1, KC_ACL2, XXXXXXX, KC_BTN1,
                             KC_BTN3, KC_BTN2, KC_BTN1, KC_TRNS,            KC_TRNS,  KC_LSFT, C(KC_LSFT), KC_DEL
),
/* NUMBERS AND SYMBOLS
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  | F6   |                    |  F7  |  F8  |  F9  | F10  |  F11 | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TRAN |  ||  |  &   |  *   |  (   | )    |                    |  SUM |  7   |  8   |  9   |  -   |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TRAN |  [   |  $   |  %   |  ^   |  /   |-------.    ,-------|   =  |  4   |  5   |  6   |  +   |      |
 * |------+------+------+------+------+------| TRAN  |    | TRAN  |------+------+------+------+------+------|
 * | TRAN |  ]   |  !   |  @   |  #   |  \   |-------|    |-------|   0  |  1   |  2   |  3   |   .  | TRAN |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | TRAN | TRAN | TRAN | / TRAN  /       \ TRAN \  | TRAN | TRAN | TRAN |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_NUM] = LAYOUT(
  KC_F1,   KC_F2,      KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,    KC_F8, KC_F9, KC_F10, KC_F11,      KC_F12,
  KC_TRNS, SPOILER,    S(KC_7), S(KC_8), S(KC_9), S(KC_0),                   SUM,      KC_7,  KC_8,  KC_9,   KC_MINS,     XXXXXXX,
  KC_TRNS, TD_BRAC_OP, S(KC_4), S(KC_5), S(KC_6), KC_SLSH,                   KC_EQUAL, KC_4,  KC_5,  KC_6,   S(KC_EQUAL), XXXXXXX,
  KC_TRNS, TD_BRAC_CL, S(KC_1), S(KC_2), S(KC_3), KC_BSLS, KC_TRNS, KC_TRNS, KC_0,     KC_1,  KC_2,  KC_3,   KC_DOT,      KC_TRNS,
                           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS
  )
};
