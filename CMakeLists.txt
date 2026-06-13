# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(lvgl)

FILE(GLOB app_sources src/*.c img_out/*.c)
target_sources(app PRIVATE ${app_sources})

# Add LVGL GIF widget (not included by default in Zephyr's LVGL module)
target_sources(app PRIVATE
    ${ZEPHYR_LVGL_MODULE_DIR}/src/widgets/gif/lv_gif.c
)
