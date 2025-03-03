# SPDX-License-Identifier: MIT
target_sources(app PRIVATE src/trackball.c)
board_runner_args(pyocd "--target=nrf52840")
set(OPENOCD_NRF5_INTERFACE "cmsis-dap")
include(${ZEPHYR_BASE}/boards/common/pyocd.board.cmake)
