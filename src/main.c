/*
 * Copyright (c) 2018 Jan Van Winkel <jan.van_winkel@dxplore.eu>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <lvgl.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/display.h>
#include <zephyr/input/input.h>
#include <zephyr/kernel.h>
#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app);

#include "gif_frames/include/gif_frames.h"
static const lv_image_dsc_t *adore_frames[] = {
    &adore_frame_000, &adore_frame_001, &adore_frame_002, &adore_frame_003,
    &adore_frame_004, &adore_frame_005, &adore_frame_006, &adore_frame_007,
    &adore_frame_008, &adore_frame_009, &adore_frame_010, &adore_frame_011,
    &adore_frame_012, &adore_frame_013, &adore_frame_014, &adore_frame_015,
    &adore_frame_016, &adore_frame_017, &adore_frame_018, &adore_frame_019,
    &adore_frame_020, &adore_frame_021, &adore_frame_022, &adore_frame_023,
    &adore_frame_024,
};

static const lv_image_dsc_t *buzzing_frames[] = {
    &buzzing_frame_000, &buzzing_frame_001, &buzzing_frame_002,
    &buzzing_frame_003, &buzzing_frame_004, &buzzing_frame_005,
    &buzzing_frame_006, &buzzing_frame_007, &buzzing_frame_008,
    &buzzing_frame_009, &buzzing_frame_010, &buzzing_frame_011,
    &buzzing_frame_012, &buzzing_frame_013, &buzzing_frame_014,
    &buzzing_frame_015, &buzzing_frame_016, &buzzing_frame_017,
    &buzzing_frame_018, &buzzing_frame_019, &buzzing_frame_020,
    &buzzing_frame_021, &buzzing_frame_022, &buzzing_frame_023,
    &buzzing_frame_024, &buzzing_frame_025, &buzzing_frame_026,
    &buzzing_frame_027, &buzzing_frame_028, &buzzing_frame_029,
    &buzzing_frame_030, &buzzing_frame_031, &buzzing_frame_032,
    &buzzing_frame_033, &buzzing_frame_034, &buzzing_frame_035,
    &buzzing_frame_036, &buzzing_frame_037, &buzzing_frame_038,
    &buzzing_frame_039, &buzzing_frame_040, &buzzing_frame_041,
    &buzzing_frame_042, &buzzing_frame_043, &buzzing_frame_044,
    &buzzing_frame_045, &buzzing_frame_046, &buzzing_frame_047,
    &buzzing_frame_048, &buzzing_frame_049, &buzzing_frame_050,
    &buzzing_frame_051, &buzzing_frame_052, &buzzing_frame_053,
    &buzzing_frame_054, &buzzing_frame_055, &buzzing_frame_056,
    &buzzing_frame_057, &buzzing_frame_058, &buzzing_frame_059,
    &buzzing_frame_060, &buzzing_frame_061, &buzzing_frame_062,
    &buzzing_frame_063, &buzzing_frame_064, &buzzing_frame_065,
    &buzzing_frame_066,
};

static const lv_image_dsc_t *dizzy_frames[] = {
    &dizzy_frame_000, &dizzy_frame_001, &dizzy_frame_002, &dizzy_frame_003,
    &dizzy_frame_004, &dizzy_frame_005, &dizzy_frame_006, &dizzy_frame_007,
    &dizzy_frame_008, &dizzy_frame_009, &dizzy_frame_010, &dizzy_frame_011,
    &dizzy_frame_012, &dizzy_frame_013, &dizzy_frame_014, &dizzy_frame_015,
    &dizzy_frame_016, &dizzy_frame_017, &dizzy_frame_018, &dizzy_frame_019,
    &dizzy_frame_020, &dizzy_frame_021, &dizzy_frame_022, &dizzy_frame_023,
    &dizzy_frame_024, &dizzy_frame_025, &dizzy_frame_026, &dizzy_frame_027,
    &dizzy_frame_028, &dizzy_frame_029, &dizzy_frame_030, &dizzy_frame_031,
    &dizzy_frame_032, &dizzy_frame_033, &dizzy_frame_034, &dizzy_frame_035,
    &dizzy_frame_036, &dizzy_frame_037, &dizzy_frame_038, &dizzy_frame_039,
    &dizzy_frame_040, &dizzy_frame_041, &dizzy_frame_042, &dizzy_frame_043,
    &dizzy_frame_044, &dizzy_frame_045, &dizzy_frame_046,
};

static const lv_image_dsc_t *down_frames[] = {
    &down_frame_000, &down_frame_001, &down_frame_002, &down_frame_003,
    &down_frame_004, &down_frame_005, &down_frame_006, &down_frame_007,
    &down_frame_008, &down_frame_009, &down_frame_010, &down_frame_011,
    &down_frame_012, &down_frame_013, &down_frame_014, &down_frame_015,
    &down_frame_016, &down_frame_017, &down_frame_018, &down_frame_019,
    &down_frame_020, &down_frame_021, &down_frame_022, &down_frame_023,
    &down_frame_024, &down_frame_025, &down_frame_026, &down_frame_027,
    &down_frame_028, &down_frame_029, &down_frame_030, &down_frame_031,
    &down_frame_032, &down_frame_033, &down_frame_034, &down_frame_035,
    &down_frame_036, &down_frame_037, &down_frame_038, &down_frame_039,
    &down_frame_040, &down_frame_041, &down_frame_042, &down_frame_043,
    &down_frame_044, &down_frame_045, &down_frame_046,
};

static const lv_image_dsc_t *energetic_frames[] = {
    &energetic_frame_000, &energetic_frame_001, &energetic_frame_002,
    &energetic_frame_003, &energetic_frame_004, &energetic_frame_005,
    &energetic_frame_006, &energetic_frame_007, &energetic_frame_008,
    &energetic_frame_009, &energetic_frame_010, &energetic_frame_011,
    &energetic_frame_012, &energetic_frame_013, &energetic_frame_014,
    &energetic_frame_015, &energetic_frame_016, &energetic_frame_017,
    &energetic_frame_018, &energetic_frame_019, &energetic_frame_020,
    &energetic_frame_021, &energetic_frame_022, &energetic_frame_023,
    &energetic_frame_024, &energetic_frame_025, &energetic_frame_026,
    &energetic_frame_027, &energetic_frame_028, &energetic_frame_029,
    &energetic_frame_030, &energetic_frame_031, &energetic_frame_032,
    &energetic_frame_033, &energetic_frame_034, &energetic_frame_035,
    &energetic_frame_036, &energetic_frame_037, &energetic_frame_038,
    &energetic_frame_039, &energetic_frame_040, &energetic_frame_041,
    &energetic_frame_042, &energetic_frame_043, &energetic_frame_044,
    &energetic_frame_045, &energetic_frame_046, &energetic_frame_047,
    &energetic_frame_048, &energetic_frame_049, &energetic_frame_050,
    &energetic_frame_051, &energetic_frame_052, &energetic_frame_053,
    &energetic_frame_054, &energetic_frame_055, &energetic_frame_056,
    &energetic_frame_057, &energetic_frame_058, &energetic_frame_059,
    &energetic_frame_060, &energetic_frame_061, &energetic_frame_062,
    &energetic_frame_063, &energetic_frame_064, &energetic_frame_065,
    &energetic_frame_066, &energetic_frame_067, &energetic_frame_068,
    &energetic_frame_069, &energetic_frame_070, &energetic_frame_071,
    &energetic_frame_072, &energetic_frame_073, &energetic_frame_074,
    &energetic_frame_075, &energetic_frame_076, &energetic_frame_077,
    &energetic_frame_078, &energetic_frame_079, &energetic_frame_080,
    &energetic_frame_081, &energetic_frame_082, &energetic_frame_083,
    &energetic_frame_084, &energetic_frame_085, &energetic_frame_086,
    &energetic_frame_087, &energetic_frame_088, &energetic_frame_089,
    &energetic_frame_090, &energetic_frame_091, &energetic_frame_092,
    &energetic_frame_093, &energetic_frame_094, &energetic_frame_095,
    &energetic_frame_096, &energetic_frame_097, &energetic_frame_098,
};

static const lv_image_dsc_t *happ_frames[] = {
    &happ_frame_000, &happ_frame_001, &happ_frame_002, &happ_frame_003,
    &happ_frame_004, &happ_frame_005, &happ_frame_006, &happ_frame_007,
    &happ_frame_008, &happ_frame_009, &happ_frame_010, &happ_frame_011,
    &happ_frame_012, &happ_frame_013, &happ_frame_014, &happ_frame_015,
    &happ_frame_016, &happ_frame_017, &happ_frame_018, &happ_frame_019,
    &happ_frame_020, &happ_frame_021, &happ_frame_022, &happ_frame_023,
    &happ_frame_024, &happ_frame_025, &happ_frame_026, &happ_frame_027,
    &happ_frame_028, &happ_frame_029, &happ_frame_030, &happ_frame_031,
    &happ_frame_032, &happ_frame_033, &happ_frame_034, &happ_frame_035,
    &happ_frame_036, &happ_frame_037, &happ_frame_038, &happ_frame_039,
    &happ_frame_040, &happ_frame_041, &happ_frame_042, &happ_frame_043,
    &happ_frame_044, &happ_frame_045, &happ_frame_046, &happ_frame_047,
    &happ_frame_048, &happ_frame_049, &happ_frame_050, &happ_frame_051,
    &happ_frame_052, &happ_frame_053, &happ_frame_054, &happ_frame_055,
    &happ_frame_056, &happ_frame_057, &happ_frame_058, &happ_frame_059,
    &happ_frame_060, &happ_frame_061, &happ_frame_062, &happ_frame_063,
    &happ_frame_064, &happ_frame_065, &happ_frame_066, &happ_frame_067,
    &happ_frame_068, &happ_frame_069, &happ_frame_070, &happ_frame_071,
    &happ_frame_072, &happ_frame_073, &happ_frame_074,
};

static const lv_image_dsc_t *squint_frames[] = {
    &squint_frame_000, &squint_frame_001, &squint_frame_002, &squint_frame_003,
    &squint_frame_004, &squint_frame_005, &squint_frame_006, &squint_frame_007,
    &squint_frame_008, &squint_frame_009, &squint_frame_010, &squint_frame_011,
    &squint_frame_012, &squint_frame_013, &squint_frame_014, &squint_frame_015,
    &squint_frame_016, &squint_frame_017, &squint_frame_018, &squint_frame_019,
    &squint_frame_020, &squint_frame_021, &squint_frame_022, &squint_frame_023,
    &squint_frame_024, &squint_frame_025, &squint_frame_026, &squint_frame_027,
    &squint_frame_028, &squint_frame_029, &squint_frame_030, &squint_frame_031,
    &squint_frame_032, &squint_frame_033, &squint_frame_034, &squint_frame_035,
    &squint_frame_036, &squint_frame_037, &squint_frame_038, &squint_frame_039,
};

static const lv_image_dsc_t *sparkle_frames[] = {
    &sparkle_frame_000, &sparkle_frame_001, &sparkle_frame_002,
    &sparkle_frame_003, &sparkle_frame_004, &sparkle_frame_005,
    &sparkle_frame_006, &sparkle_frame_007, &sparkle_frame_008,
    &sparkle_frame_009, &sparkle_frame_010, &sparkle_frame_011,
    &sparkle_frame_012, &sparkle_frame_013, &sparkle_frame_014,
    &sparkle_frame_015, &sparkle_frame_016, &sparkle_frame_017,
    &sparkle_frame_018, &sparkle_frame_019, &sparkle_frame_020,
    &sparkle_frame_021, &sparkle_frame_022, &sparkle_frame_023,
    &sparkle_frame_024, &sparkle_frame_025, &sparkle_frame_026,
    &sparkle_frame_027, &sparkle_frame_028, &sparkle_frame_029,
    &sparkle_frame_030, &sparkle_frame_031, &sparkle_frame_032,
    &sparkle_frame_033, &sparkle_frame_034, &sparkle_frame_035,
    &sparkle_frame_036, &sparkle_frame_037, &sparkle_frame_038,
    &sparkle_frame_039, &sparkle_frame_040, &sparkle_frame_041,
    &sparkle_frame_042, &sparkle_frame_043, &sparkle_frame_044,
};

static const lv_image_dsc_t **frames = adore_frames;

#define FRAME_COUNT 24

static lv_obj_t *img;
static uint8_t current_frame = 0;
// todo: have a method to calculate the number of frames
static uint8_t frame_max_count = 0;

static void anim_cb(lv_timer_t *t) {
  current_frame++;
  if (current_frame >= frame_max_count) {
    current_frame = 0;
  }
  lv_image_set_src(img, frames[current_frame]);
}

static void on_button_press(struct input_event *evt, void *user_data) {
  static uint8_t type = 0;
  switch (type) {
  case 2:
    frames = adore_frames;
    frame_max_count = 24;
    break;
  case 4:
    frames = buzzing_frames;
    frame_max_count = 66;
    break;
  case 6:
    frames = dizzy_frames;
    frame_max_count = 46;
    break;
  case 8:
    frames = down_frames;
    frame_max_count = 46;
    break;
  case 10:
    frames = energetic_frames;
    frame_max_count = 98;
    break;
  case 12:
    frames = happ_frames;
    frame_max_count = 74;
    break;
  case 14:
    frames = sparkle_frames;
    frame_max_count = 44;
    break;
  case 16:
    frames = squint_frames;
    frame_max_count = 39;
    break;
  default:
    if (!(type & 1)) {
      type = 0;
      frames = adore_frames;
      frame_max_count = 24;
    }
  }
  printf("mone enne vilichittund %d\n", type);
  type++;
}

// struct k_timer my_timer;
// K_TIMER_DEFINE(my_timer, on_button_press, NULL);

INPUT_CALLBACK_DEFINE(NULL, on_button_press, NULL);

int main(void) {
  const struct device *display_dev;
  int ret;

  display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
  if (!device_is_ready(display_dev)) {
    LOG_ERR("Device not ready, aborting test");
    return 0;
  }

  ret = display_blanking_off(display_dev);
  if (ret < 0 && ret != -ENOSYS) {
    LOG_ERR("Failed to turn blanking off (error %d)", ret);
    return 0;
  }
  //   k_timer_init(&my_timer, on_button_press, NULL);

  //   k_timer_start(&my_timer, K_SECONDS(1), K_SECONDS(5));
  /* Create image object */
  img = lv_image_create(lv_screen_active());
  lv_image_set_src(img, frames[0]);
  lv_obj_center(img);

  /* Create animation timer - 100ms per frame = 10 FPS */
  lv_timer_create(anim_cb, 100, NULL);

  while (1) {
    lv_timer_handler();
    k_sleep(K_MSEC(10));
  }
}
