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
#define DECLARE_FRAME(n) LV_IMG_DECLARE(adore_frame_##n)

DECLARE_FRAME(000);
DECLARE_FRAME(001);
DECLARE_FRAME(002);
DECLARE_FRAME(003);
DECLARE_FRAME(004);
DECLARE_FRAME(005);
DECLARE_FRAME(006);
DECLARE_FRAME(007);
DECLARE_FRAME(008);
DECLARE_FRAME(009);
DECLARE_FRAME(010);
DECLARE_FRAME(011);
DECLARE_FRAME(012);
DECLARE_FRAME(013);
DECLARE_FRAME(014);
DECLARE_FRAME(015);
DECLARE_FRAME(016);
DECLARE_FRAME(017);
DECLARE_FRAME(018);
DECLARE_FRAME(019);
DECLARE_FRAME(020);
DECLARE_FRAME(021);
DECLARE_FRAME(022);
DECLARE_FRAME(023);
DECLARE_FRAME(024);

static const lv_image_dsc_t *adore_frames[] = {
    &adore_frame_000, &adore_frame_001, &adore_frame_002, &adore_frame_003,
    &adore_frame_004, &adore_frame_005, &adore_frame_006, &adore_frame_007,
    &adore_frame_008, &adore_frame_009, &adore_frame_010, &adore_frame_011,
    &adore_frame_012, &adore_frame_013, &adore_frame_014, &adore_frame_015,
    &adore_frame_016, &adore_frame_017, &adore_frame_018, &adore_frame_019,
    &adore_frame_020, &adore_frame_021, &adore_frame_022, &adore_frame_023,
    &adore_frame_024,
};

#define DECLARE_FRAME_BUZZ(n) LV_IMG_DECLARE(buzzing_frame_##n)

DECLARE_FRAME_BUZZ(000);
DECLARE_FRAME_BUZZ(001);
DECLARE_FRAME_BUZZ(002);
DECLARE_FRAME_BUZZ(003);
DECLARE_FRAME_BUZZ(004);
DECLARE_FRAME_BUZZ(005);
DECLARE_FRAME_BUZZ(006);
DECLARE_FRAME_BUZZ(007);
DECLARE_FRAME_BUZZ(008);
DECLARE_FRAME_BUZZ(009);
DECLARE_FRAME_BUZZ(010);
DECLARE_FRAME_BUZZ(011);
DECLARE_FRAME_BUZZ(012);
DECLARE_FRAME_BUZZ(013);
DECLARE_FRAME_BUZZ(014);
DECLARE_FRAME_BUZZ(015);
DECLARE_FRAME_BUZZ(016);
DECLARE_FRAME_BUZZ(017);
DECLARE_FRAME_BUZZ(018);
DECLARE_FRAME_BUZZ(019);
DECLARE_FRAME_BUZZ(020);
DECLARE_FRAME_BUZZ(021);
DECLARE_FRAME_BUZZ(022);
DECLARE_FRAME_BUZZ(023);
DECLARE_FRAME_BUZZ(024);
DECLARE_FRAME_BUZZ(025);
DECLARE_FRAME_BUZZ(026);
DECLARE_FRAME_BUZZ(027);
DECLARE_FRAME_BUZZ(028);
DECLARE_FRAME_BUZZ(029);
DECLARE_FRAME_BUZZ(030);
DECLARE_FRAME_BUZZ(031);
DECLARE_FRAME_BUZZ(032);
DECLARE_FRAME_BUZZ(033);
DECLARE_FRAME_BUZZ(034);
DECLARE_FRAME_BUZZ(035);
DECLARE_FRAME_BUZZ(036);
DECLARE_FRAME_BUZZ(037);
DECLARE_FRAME_BUZZ(038);
DECLARE_FRAME_BUZZ(039);
DECLARE_FRAME_BUZZ(040);
DECLARE_FRAME_BUZZ(041);
DECLARE_FRAME_BUZZ(042);
DECLARE_FRAME_BUZZ(043);
DECLARE_FRAME_BUZZ(044);
DECLARE_FRAME_BUZZ(045);
DECLARE_FRAME_BUZZ(046);
DECLARE_FRAME_BUZZ(047);
DECLARE_FRAME_BUZZ(048);
DECLARE_FRAME_BUZZ(049);
DECLARE_FRAME_BUZZ(050);
DECLARE_FRAME_BUZZ(051);
DECLARE_FRAME_BUZZ(052);
DECLARE_FRAME_BUZZ(053);
DECLARE_FRAME_BUZZ(054);
DECLARE_FRAME_BUZZ(055);
DECLARE_FRAME_BUZZ(056);
DECLARE_FRAME_BUZZ(057);
DECLARE_FRAME_BUZZ(058);
DECLARE_FRAME_BUZZ(059);
DECLARE_FRAME_BUZZ(060);
DECLARE_FRAME_BUZZ(061);
DECLARE_FRAME_BUZZ(062);
DECLARE_FRAME_BUZZ(063);
DECLARE_FRAME_BUZZ(064);
DECLARE_FRAME_BUZZ(065);
DECLARE_FRAME_BUZZ(066);
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

static const lv_image_dsc_t **frames = adore_frames;

#define FRAME_COUNT 24

static lv_obj_t *img;
static uint8_t current_frame = 0;

static void anim_cb(lv_timer_t *t) {
  current_frame++;
  if (current_frame >= FRAME_COUNT) {
    current_frame = 0;
  }
  lv_image_set_src(img, frames[current_frame]);
}

static void on_button_press(struct input_event *evt, void *user_data) {
  static uint8_t type = 0;
  switch (type) {
  case 2:
    frames = adore_frames;
    break;
  case 4:
    frames = buzzing_frames;

    break;
  case 6:
    frames = adore_frames;

    break;
  case 8:
    frames = buzzing_frames;

    break;
  case 10:
    frames = adore_frames;

    break;
  default:
    if (!(type & 1)) {
      type = 0;
      frames = buzzing_frames;
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
