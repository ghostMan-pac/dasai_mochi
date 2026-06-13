/*
 * Copyright (c) 2018 Jan Van Winkel <jan.van_winkel@dxplore.eu>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/display.h>
#include <zephyr/kernel.h>
#include <lvgl.h>
#include "widgets/gif/lv_gif.h"

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app);

LV_IMG_DECLARE(squint_gif);

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

	/* Create GIF object */
	lv_obj_t *gif = lv_gif_create(lv_screen_active());
	lv_gif_set_src(gif, &squint_gif);
	lv_obj_center(gif);

	while (1) {
		lv_timer_handler();
		k_sleep(K_MSEC(10));
	}
}
