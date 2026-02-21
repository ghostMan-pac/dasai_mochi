/*
 * Copyright (c) 2018 Jan Van Winkel <jan.van_winkel@dxplore.eu>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/display.h>
#include <zephyr/drivers/gpio.h>
#include <lvgl.h>
#include <stdio.h>
#include <string.h>
#include <zephyr/kernel.h>
#include <lvgl_input_device.h>
#include <lvgl.h>

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app);
#define DECLARE_FRAME(n) LV_IMG_DECLARE(frame_##n)

/* 0 - 9 */
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

/* 10 - 19 */
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

/* 20 - 29 */
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

/* 30 - 39 */
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

/* 40 - 49 */
DECLARE_FRAME(040);
DECLARE_FRAME(041);
DECLARE_FRAME(042);
DECLARE_FRAME(043);
DECLARE_FRAME(044);
DECLARE_FRAME(045);
DECLARE_FRAME(046);
DECLARE_FRAME(047);
DECLARE_FRAME(048);
DECLARE_FRAME(049);

/* 50 - 59 */
DECLARE_FRAME(050);
DECLARE_FRAME(051);
DECLARE_FRAME(052);
DECLARE_FRAME(053);
DECLARE_FRAME(054);
DECLARE_FRAME(055);
DECLARE_FRAME(056);
DECLARE_FRAME(057);
DECLARE_FRAME(058);
DECLARE_FRAME(059);

/* 60 - 69 */
DECLARE_FRAME(060);
DECLARE_FRAME(061);
DECLARE_FRAME(062);
DECLARE_FRAME(063);
DECLARE_FRAME(064);
DECLARE_FRAME(065);
DECLARE_FRAME(066);
DECLARE_FRAME(067);
DECLARE_FRAME(068);
DECLARE_FRAME(069);

/* 70 - 73 */
DECLARE_FRAME(070);
DECLARE_FRAME(071);
DECLARE_FRAME(072);
DECLARE_FRAME(073);

static const lv_image_dsc_t *frames[] = {
	&frame_000, &frame_001, &frame_002, &frame_003, &frame_004, &frame_005, &frame_006,
	&frame_007, &frame_008, &frame_009, &frame_010, &frame_011, &frame_012, &frame_013,
	&frame_014, &frame_015, &frame_016, &frame_017, &frame_018, &frame_019, &frame_020,
	&frame_021, &frame_022, &frame_023, &frame_024, &frame_025, &frame_026, &frame_027,
	&frame_028, &frame_029, &frame_030, &frame_031, &frame_032, &frame_033, &frame_034,
	&frame_035, &frame_036, &frame_037, &frame_038, &frame_039, &frame_040, &frame_041,
	&frame_042, &frame_043, &frame_044, &frame_045, &frame_046, &frame_047, &frame_048,
	&frame_049, &frame_050, &frame_051, &frame_052, &frame_053, &frame_054, &frame_055,
	&frame_056, &frame_057, &frame_058, &frame_059, &frame_060, &frame_061, &frame_062,
	&frame_063, &frame_064, &frame_065, &frame_066, &frame_067, &frame_068, &frame_069,
	&frame_070, &frame_071, &frame_072, &frame_073};
#define FRAME_COUNT (sizeof(frames) / sizeof(frames[0]))

static lv_obj_t *img;
static uint8_t current_frame = 0;

/* Timer callback */
static void anim_cb(lv_timer_t *t)
{
	current_frame++;
	if (current_frame >= FRAME_COUNT) {
		current_frame = 0;
	}

	lv_image_set_src(img, frames[current_frame]);
}

int main(void)
{
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
	// display_set_invert(display_dev, true);


	/* Create image object */
	img = lv_image_create(lv_screen_active());
	lv_image_set_src(img, frames[0]);
	lv_obj_center(img);

	/* Create animation timer */
	lv_timer_create(anim_cb, 120, NULL); 

	while (1) {
		lv_timer_handler();
		k_sleep(K_MSEC(10));
	}
}
