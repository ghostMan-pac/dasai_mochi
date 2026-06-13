# GIF Conversion Utils

Two scripts to prepare GIFs for LVGL monochrome displays.

## Requirements

```bash
pip install Pillow
```

---

## Script 1: resize_gif.py

Resize any GIF to any target dimensions.

### Usage

```bash
python resize_gif.py <input.gif> --width <W> --height <H>
```

### Examples

```bash
# For SSD1306 128x64 OLED
python resize_gif.py squint.gif --width 128 --height 64

# For SSD1306 128x32 OLED
python resize_gif.py squint.gif --width 128 --height 32

# For SH1106 132x64 OLED
python resize_gif.py squint.gif --width 132 --height 64

# For ST7789 240x240 LCD
python resize_gif.py squint.gif --width 240 --height 240

# For ST7735 160x128 LCD
python resize_gif.py squint.gif --width 160 --height 128

# Custom output filename
python resize_gif.py squint.gif --width 128 --height 64 --output my_resized.gif
```

### Options

| Option | Short | Required | Description |
|--------|-------|----------|-------------|
| `--width` | `-W` | Yes | Target width in pixels |
| `--height` | `-H` | Yes | Target height in pixels |
| `--output` | `-o` | No | Output filename (default: input_WxH.gif) |

---

## Script 2: gif_to_lvgl.py

Convert GIF to LVGL C source files (1-bit format for monochrome displays).

### Usage

```bash
python gif_to_lvgl.py <input.gif> --output <dir> --prefix <name>
```

### Examples

```bash
# Basic conversion
python gif_to_lvgl.py squint_128x64.gif --output ../src --prefix squint_frame

# With color inversion
python gif_to_lvgl.py dark_gif.gif --output ../src --prefix my_frame --invert

# Adjust threshold
python gif_to_lvgl.py low_contrast.gif --output ../src --prefix frame --threshold 100
```

### Options

| Option | Short | Default | Description |
|--------|-------|---------|-------------|
| `--output` | `-o` | `.` | Output directory |
| `--prefix` | `-p` | frame | Frame name prefix |
| `--threshold` | `-t` | 128 | Brightness threshold (0-255) |
| `--invert` | `-i` | False | Invert colors |

---

## Complete Workflow

### Step 1: Resize GIF to your display size

```bash
python resize_gif.py ../src/squint.gif --width 128 --height 64
```

Output: `squint_128x64.gif`

### Step 2: Convert to C files

```bash
python gif_to_lvgl.py ../src/squint_128x64.gif --output ../src --prefix squint_frame
```

Output:
```
src/squint_frame_000.c
src/squint_frame_001.c
...
src/squint_frame_039.c
```

### Step 3: Build project

```bash
west build -b <your_board> -p -- -DSHIELD=<your_display>
west flash
```

---

## Common Display Sizes

| Display | Resolution | Command |
|---------|------------|---------|
| SSD1306 OLED | 128x64 | `--width 128 --height 64` |
| SSD1306 OLED | 128x32 | `--width 128 --height 32` |
| SH1106 OLED | 132x64 | `--width 132 --height 64` |
| ST7789 LCD | 240x240 | `--width 240 --height 240` |
| ST7735 LCD | 160x128 | `--width 160 --height 128` |
| ILI9341 LCD | 320x240 | `--width 320 --height 240` |

---

## Troubleshooting

| Problem | Solution |
|---------|----------|
| Blue/solid screen | Try `--invert` flag |
| Too dark/light | Adjust `--threshold` (lower = more white) |
| Distorted image | Check aspect ratio when resizing |
