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

static const lv_image_dsc_t *frames[] = {
	&adore_frame_000, &adore_frame_001, &adore_frame_002, &adore_frame_003, &adore_frame_004,
	&adore_frame_005, &adore_frame_006, &adore_frame_007, &adore_frame_008, &adore_frame_009,
	&adore_frame_010, &adore_frame_011, &adore_frame_012, &adore_frame_013, &adore_frame_014,
	&adore_frame_015, &adore_frame_016, &adore_frame_017, &adore_frame_018, &adore_frame_019,
	&adore_frame_020, &adore_frame_021, &adore_frame_022, &adore_frame_023, &adore_frame_024,
};
#define FRAME_COUNT (sizeof(frames) / sizeof(frames[0]))

static lv_obj_t *img;
static uint8_t current_frame = 0;

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
