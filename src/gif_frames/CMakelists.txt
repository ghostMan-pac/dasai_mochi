# SPDX-License-Identifier: Apache-2.0

FILE(GLOB_RECURSE gif_frame_sources *.c)
target_sources(app PRIVATE ${gif_frame_sources})
