# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(dasai_mochi)

zephyr_library_sources_ifdef(CONFIG_USE_FRAMES_METHOD src/main_w_frames.c)
zephyr_library_sources_ifdef(CONFIG_USE_GIF_METHOD src/main_gif_fs.c)

add_subdirectory(src/gif_frames)