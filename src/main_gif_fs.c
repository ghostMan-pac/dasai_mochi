/*
 * GIF from LittleFS demo
 * Writes embedded GIF to filesystem on first boot, then plays it using LVGL GIF decoder
 */

#include <lvgl.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/display.h>
#include <zephyr/fs/fs.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(app);

/* Embedded GIF data - will be written to filesystem on first boot */
#include "microchip_gif.h"

#define GIF_PATH "/lfs1/microchip.gif"

static lv_obj_t *gif_obj;

/* Check if file exists */
static bool file_exists(const char *path)
{
	struct fs_dirent entry;
	return fs_stat(path, &entry) == 0;
}

/* Write embedded GIF to filesystem */
static int write_gif_to_fs(void)
{
	struct fs_file_t file;
	int ret;

	if (file_exists(GIF_PATH)) {
		LOG_INF("GIF already exists in filesystem");
		return 0;
	}

	LOG_INF("Writing GIF to filesystem...");

	fs_file_t_init(&file);
	ret = fs_open(&file, GIF_PATH, FS_O_CREATE | FS_O_WRITE);
	if (ret < 0) {
		LOG_ERR("Failed to open file for writing: %d", ret);
		return ret;
	}

	ret = fs_write(&file, microchip_gif_data, microchip_gif_data_len);
	if (ret < 0) {
		LOG_ERR("Failed to write GIF data: %d", ret);
		fs_close(&file);
		return ret;
	}

	fs_close(&file);
	LOG_INF("GIF written successfully (%u bytes)", microchip_gif_data_len);
	return 0;
}

int main(void)
{
	const struct device *display_dev;
	int ret;

	display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
	if (!device_is_ready(display_dev)) {
		LOG_ERR("Display device not ready");
		return 0;
	}

	ret = display_blanking_off(display_dev);
	if (ret < 0 && ret != -ENOSYS) {
		LOG_ERR("Failed to turn blanking off: %d", ret);
		return 0;
	}

	/* Write GIF to filesystem (only on first boot) */
	ret = write_gif_to_fs();
	if (ret < 0) {
		LOG_ERR("Failed to write GIF to filesystem");
		return 0;
	}

	/* Create GIF object and load from filesystem */
	gif_obj = lv_gif_create(lv_screen_active());
	if (gif_obj == NULL) {
		LOG_ERR("Failed to create GIF object");
		return 0;
	}

	/* Load GIF from filesystem path */
	lv_gif_set_src(gif_obj, GIF_PATH);
	lv_obj_center(gif_obj);

	LOG_INF("GIF loaded from %s", GIF_PATH);

	/* Main loop */
	while (1) {
		lv_timer_handler();
		k_sleep(K_MSEC(10));
	}
}
