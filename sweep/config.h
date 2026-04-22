#pragma once

#define USE_SERIAL
#define SERIAL_USART_TX_PIN GP1

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U
#define RP2040_FLASH_GD25Q64CS

#define SPLIT_LAYER_STATE_ENABLE
// #define SPLIT_OLED_ENABLE
// #define OLED_BRIGHTNESS 10

// Auto Shift
// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_auto_shift.md
// #define AUTO_SHIFT_TIMEOUT 130
// Tapping term
#define TAPPING_TERM 150
#define TAPPING_TERM_PER_KEY

#define RETRO_TAPPING
#define RETRO_TAPPING_PER_KEY
// combos
#define EXTRA_SHORT_COMBOS
#define COMBO_ONLY_FROM_LAYER 0

// Mouse key settings
#define MK_3_SPEED
#define MK_MOMENTARY_ACCEL
#define MK_C_OFFSET_UNMOD 4
#define MK_C_INTERVAL_UNMOD 16
