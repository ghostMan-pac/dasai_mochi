/*
 * Copyright (c) 2018 Jan Van Winkel <jan.van_winkel@dxplore.eu>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <lvgl.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/display.h>
#include <zephyr/kernel.h>

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app);

#define DECLARE_FRAME(n) LV_IMG_DECLARE(adore_##n)

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
DECLARE_FRAME(025);
DECLARE_FRAME(026);
DECLARE_FRAME(027);
DECLARE_FRAME(028);
DECLARE_FRAME(029);
DECLARE_FRAME(030);
DECLARE_FRAME(031);
DECLARE_FRAME(032);
DECLARE_FRAME(033);
DECLARE_FRAME(034);
DECLARE_FRAME(035);
DECLARE_FRAME(036);
DECLARE_FRAME(037);
DECLARE_FRAME(038);
DECLARE_FRAME(039);
// static const lv_image_dsc_t *squint_frames[] = {
//     &squint_frame_000, &squint_frame_001, &squint_frame_002, &squint_frame_003,
//     &squint_frame_004, &squint_frame_005, &squint_frame_006, &squint_frame_007,
//     &squint_frame_008, &squint_frame_009, &squint_frame_010, &squint_frame_011,
//     &squint_frame_012, &squint_frame_013, &squint_frame_014, &squint_frame_015,
//     &squint_frame_016, &squint_frame_017, &squint_frame_018, &squint_frame_019,
//     &squint_frame_020, &squint_frame_021, &squint_frame_022, &squint_frame_023,
//     &squint_frame_024, &squint_frame_025, &squint_frame_026, &squint_frame_027,
//     &squint_frame_028, &squint_frame_029, &squint_frame_030, &squint_frame_031,
//     &squint_frame_032, &squint_frame_033, &squint_frame_034, &squint_frame_035,
//     &squint_frame_036, &squint_frame_037, &squint_frame_038, &squint_frame_039,
// };
static const lv_image_dsc_t *frames[] = {
    &adore_000, &adore_001, &adore_002, &adore_003, &adore_004,
    &adore_005, &adore_006, &adore_007, &adore_008, &adore_009,
    &adore_010, &adore_011, &adore_012, &adore_013, &adore_014,
    &adore_015, &adore_016, &adore_017, &adore_018, &adore_019,
    &adore_020, &adore_021, &adore_022, &adore_023, &adore_024,
};
#define FRAME_COUNT (sizeof(frames) / sizeof(frames[0]))

static lv_obj_t *img;
static uint8_t current_frame = 0;

static void anim_cb(lv_timer_t *t) {
  current_frame++;
  if (current_frame >= FRAME_COUNT) {
    current_frame = 0;
  }
  lv_image_set_src(img, frames[current_frame]);
}

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
