# ============================================================================
# CIRCUIT RGB EFFECT - BUILD CONFIGURATION
# ============================================================================
# This rules.mk file enables RGB matrix support for the custom circuit effect
# ============================================================================

# Core RGB matrix functionality
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_CUSTOM_USER = yes

# Circuit effect specific dependencies
POINTING_DEVICE_DRIVER = analog_joystick
POINTING_DEVICE_ENABLE = no
COMBO_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
TAP_DANCE_ENABLE = yes
AUDIO_ENABLE = yes
CONSOLE_ENABLE = yes
DEBUG_ENABLE = yes
# Additional source files for circuit effect
#SRC += vim_motions.c
SRC += my_taps.c
SRC += my_taps_data.c
SRC += lib/oled.c

# Optional: Debug configuration for circuit effect development
# Uncomment these lines for debugging support
# CONSOLE_ENABLE = yes
# DEBUG_MATRIX_SCAN_RATE_ENABLE = yes
# LTO_ENABLE = yes
