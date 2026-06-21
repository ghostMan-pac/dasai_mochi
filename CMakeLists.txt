# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(lvgl)

# GIF from filesystem test - comment out to use original frame-based approach
target_sources(app PRIVATE src/main_gif_fs.c)

# Original frame-based approach - uncomment to use
# FILE(GLOB app_sources src/*.c)
# target_sources(app PRIVATE ${app_sources})
# add_subdirectory(src/gif_frames)