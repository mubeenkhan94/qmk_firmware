
// generated from users/manna-harbour_miryoku/miryoku.org
#define KC_LK   LWIN(KC_L) // lock Windows computer
#define KC_HD   LWIN(KC_D) // hide all windows on Windows
#define KC_NAVR LT(NAVR, KC_QUOT)
#define KC_NSL  MO(NSL)
#define KC_NSSL MO(NSSL)
#define KC_FUNL MO(FUNL)

extern uint8_t is_master;

#define LAYOUT_miryoku( \
       K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09, \
       K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19, \
       K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29, \
       N30,   N31,   K32,   K33,   K34,   K35,   K36,   K37,   N38,   N39 \
) \
LAYOUT( \
KC_FUNL, K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,   K09,   KC_HD, \
KC_NSL,  K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,   K19,   KC_NAVR, \
KC_NSSL, K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,   K29,   KC_LK, \
                     K32,   K33,   K34,   K35,   K36,   K37 \
)

#include "users/mubeen/manna-harbour_miryoku-mubeen.c"

char wpm_str[10];
uint16_t wpm_graph_timer = 0;

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_master) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_180;
    }
}

void render_crkbd_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

// #define KEYLOG_LEN (int)(32 / OLED_FONT_WIDTH)
// char keylog_str[KEYLOG_LEN] = {};
// uint8_t keylogs_str_idx = 0;
// uint16_t log_timer = 0;

// const char code_to_name[60] = {
//     ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
//     'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
//     'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
//     '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
//     'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
//     '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

// void add_keylog(uint16_t keycode) {
//     if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
//         (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }

//     for (uint8_t i = KEYLOG_LEN - 1; i > 0; i--) {
//         keylog_str[i] = keylog_str[i - 1];
//     }
//     if (keycode < 60) {
//         keylog_str[0] = code_to_name[keycode];
//     }
//     keylog_str[KEYLOG_LEN] = 0;

//     log_timer = timer_read();
// }

// void update_log(void) {
//     if (timer_elapsed(log_timer) > 750) {
//         add_keylog(0);
//     }
// }

// bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
//     if (record->event.pressed) {  add_keylog(keycode); }
//     return true;
// }

void render_status(void) {

    oled_write_P(PSTR("Layer"), false);
    switch (biton32(layer_state)) {
        case BASE:
            oled_write_P(PSTR("Base"), false);
            break;
        case NAVR:
            oled_write_P(PSTR("Nav "), false);
            break;
        case MOUR:
            oled_write_P(PSTR("Mouse"), false);
            break;
        case FUNL:
            oled_write_P(PSTR("Func"), false);
            break;
        case NSL:
            oled_write_P(PSTR("Num "), false);
            break;
        case NSSL:
            oled_write_P(PSTR("Sym "), false);
            break;
        default:
            oled_write_P(PSTR("Unkn"), false);
            break;
}

#ifdef WPM_ENABLE
    // Write WPM
    sprintf(wpm_str, "WPM: %03d", get_current_wpm());
    oled_write_P(PSTR("\n"), false);
    oled_write(wpm_str, false);
#endif
}

static uint8_t zero_bar_count = 0;
static uint8_t bar_count = 0;

static void render_wpm_graph(void) {
    uint8_t bar_height = 0;
    uint8_t bar_segment = 0;

    if (wpm_graph_timer == 0) {
	render_crkbd_logo();
	wpm_graph_timer = timer_read();
	return;
    }
    if(timer_elapsed(wpm_graph_timer) > 500) {
	wpm_graph_timer = timer_read();

	if(OLED_DISPLAY_HEIGHT == 64)
		bar_height = get_current_wpm() / 2;
	if(OLED_DISPLAY_HEIGHT == 32)
		bar_height = get_current_wpm() / 4;
	if(bar_height > OLED_DISPLAY_HEIGHT)
		bar_height = OLED_DISPLAY_HEIGHT;

	if(bar_height == 0) {
	    // keep track of how many zero bars we have drawn.  If
	    // there is a whole screen worth, turn the display off and
	    // wait until there is something to do
	    if (zero_bar_count > OLED_DISPLAY_WIDTH) {
		oled_off();
		return;
	    }
	    zero_bar_count++;
	} else
	    zero_bar_count=0;

	oled_pan(false);
	bar_count++;
	for (uint8_t i = (OLED_DISPLAY_HEIGHT / 8); i > 0; i--) {
	    if (bar_height > 7) {
		if (i % 2 == 1 && bar_count % 3 == 0)
		    bar_segment = 254;
		else
		    bar_segment = 255;
		bar_height -= 8;
	    } else {
		switch (bar_height) {
		    case 0:
			bar_segment = 0;
			break;

		    case 1:
			bar_segment = 128;
			break;

		    case 2:
			bar_segment = 192;
			break;

		    case 3:
			bar_segment = 224;
			break;

		    case 4:
			bar_segment = 240;
			break;

		    case 5:
			bar_segment = 248;
			break;

		    case 6:
			bar_segment = 252;
			break;

		    case 7:
			bar_segment = 254;
			break;
		}
		bar_height = 0;

		if (i % 2 == 1 && bar_count % 3 == 0)
		    bar_segment++;
	    }
	    oled_write_raw_byte(bar_segment, (i-1) * OLED_DISPLAY_WIDTH);
	}
    }
}

// void oled_task_user(void) {
//     if (is_keyboard_master()) {
//         render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
//     } else {
//         render_wpm_graph();
//     }
// }
// #endif

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_wpm_graph();
    } else {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    }
}
#endif

// void matrix_scan_keymap(void) { update_log(); }
