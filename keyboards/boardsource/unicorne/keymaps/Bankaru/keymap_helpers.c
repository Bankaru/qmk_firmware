void send_shift_action(uint16_t keycode) {
	uint8_t saved_mods = get_mods();
    uint8_t saved_weak = get_weak_mods();

    add_weak_mods(MOD_BIT(KC_LSFT));
    send_keyboard_report();

    tap_code(keycode);

    set_mods(saved_mods);
    set_weak_mods(saved_weak);
    send_keyboard_report();
}


void send_control_action(uint16_t keycode) {
	uint8_t saved_mods = get_mods();
    uint8_t saved_weak = get_weak_mods();

    add_weak_mods(MOD_BIT(KC_LCTL));
    send_keyboard_report();

    tap_code(keycode);

    set_mods(saved_mods);
    set_weak_mods(saved_weak);
    send_keyboard_report();
}
