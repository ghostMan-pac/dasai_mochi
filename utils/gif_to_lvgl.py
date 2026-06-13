#!/usr/bin/env python3
"""
Convert GIF to LVGL C source files for monochrome displays.

Usage:
    python gif_to_lvgl.py <input.gif> --output ../src --prefix frame

Requirements:
    pip install Pillow
"""

import argparse
import os
import sys

try:
    from PIL import Image
except ImportError:
    print("Error: Pillow library not found.")
    print("Install it with: pip install Pillow")
    sys.exit(1)


def convert_gif_to_lvgl(
    input_gif: str,
    output_dir: str,
    prefix: str,
    threshold: int,
    invert: bool,
):
    """
    Convert GIF to LVGL C source files.

    Args:
        input_gif: Path to input GIF file
        output_dir: Directory to save output .c files
        prefix: Prefix for frame names
        threshold: Brightness threshold 0-255
        invert: Invert colors if True
    """
    try:
        gif = Image.open(input_gif)
    except Exception as e:
        print(f"Error opening GIF: {e}")
        sys.exit(1)

    os.makedirs(output_dir, exist_ok=True)

    width = gif.width
    height = gif.height
    frame_count = gif.n_frames
    stride = width // 8

    print(f"Input: {input_gif}")
    print(f"Size: {width}x{height}")
    print(f"Frames: {frame_count}")
    print(f"Output: {output_dir}")
    print(f"Prefix: {prefix}")
    print("-" * 50)

    for i in range(frame_count):
        gif.seek(i)

        # Convert to grayscale
        frame = gif.convert("L")

        # Convert to 1-bit with threshold
        if invert:
            frame = frame.point(lambda x: 255 if x <= threshold else 0, mode="1")
        else:
            frame = frame.point(lambda x: 0 if x > threshold else 255, mode="1")

        raw_data = frame.tobytes()

        frame_name = f"{prefix}_{i:03d}"
        filename = os.path.join(output_dir, f"{frame_name}.c")

        with open(filename, "w") as f:
            f.write(f"""/*
 * LVGL Image Frame: {frame_name}
 * Size: {width}x{height}, Format: LV_COLOR_FORMAT_I1
 */

#include <lvgl.h>

#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

static const
LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST
uint8_t {frame_name}_map[] = {{

    /* Palette header (8 bytes): color0=black, color1=white */
    0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,

""")
            for row in range(height):
                f.write("    ")
                for col in range(stride):
                    byte_idx = row * stride + col
                    if byte_idx < len(raw_data):
                        f.write(f"0x{raw_data[byte_idx]:02x},")
                f.write("\n")

            f.write(f"""
}};

const lv_image_dsc_t {frame_name} = {{
  .header = {{
    .magic = LV_IMAGE_HEADER_MAGIC,
    .cf = LV_COLOR_FORMAT_I1,
    .flags = 0,
    .w = {width},
    .h = {height},
    .stride = {stride},
    .reserved_2 = 0,
  }},
  .data_size = sizeof({frame_name}_map),
  .data = {frame_name}_map,
  .reserved = NULL,
}};
""")
        print(f"Created: {filename}")

    print("-" * 50)
    print(f"Done! Created {frame_count} frame files.")
    data_size = (width * height // 8) + 8
    print(f"Memory: {data_size} bytes/frame, {data_size * frame_count} bytes total")


def main():
    parser = argparse.ArgumentParser(description="Convert GIF to LVGL C files")

    parser.add_argument("input", help="Input GIF file path")
    parser.add_argument("--output", "-o", default=".", help="Output directory (default: current)")
    parser.add_argument("--prefix", "-p", default="frame", help="Frame name prefix (default: frame)")
    parser.add_argument("--threshold", "-t", type=int, default=128, help="Brightness threshold 0-255 (default: 128)")
    parser.add_argument("--invert", "-i", action="store_true", help="Invert colors")

    args = parser.parse_args()

    if not os.path.exists(args.input):
        print(f"Error: Input file not found: {args.input}")
        sys.exit(1)

    convert_gif_to_lvgl(
        input_gif=args.input,
        output_dir=args.output,
        prefix=args.prefix,
        threshold=args.threshold,
        invert=args.invert,
    )


if __name__ == "__main__":
    main()
