#!/usr/bin/env python3
"""
Resize GIF to any target dimensions.

Usage:
    python resize_gif.py <input.gif> --width <W> --height <H>

Examples:
    python resize_gif.py animation.gif --width 128 --height 64
    python resize_gif.py animation.gif --width 320 --height 240
    python resize_gif.py animation.gif --width 64 --height 32

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


def resize_gif(input_gif: str, output_gif: str, width: int, height: int):
    """
    Resize GIF to target dimensions.

    Args:
        input_gif: Path to input GIF file
        output_gif: Path to output GIF file
        width: Target width in pixels
        height: Target height in pixels
    """
    try:
        gif = Image.open(input_gif)
    except Exception as e:
        print(f"Error opening GIF: {e}")
        sys.exit(1)

    print(f"Input: {input_gif}")
    print(f"Original size: {gif.width}x{gif.height}")
    print(f"Target size: {width}x{height}")
    print(f"Frames: {gif.n_frames}")

    frames = []
    durations = []

    for i in range(gif.n_frames):
        gif.seek(i)
        frame = gif.convert("RGBA").resize((width, height), Image.LANCZOS)
        frames.append(frame)
        durations.append(gif.info.get("duration", 100))

    frames[0].save(
        output_gif,
        save_all=True,
        append_images=frames[1:],
        duration=durations,
        loop=0,
    )

    print(f"Output: {output_gif}")
    print(f"Size: {os.path.getsize(output_gif)} bytes")


def main():
    parser = argparse.ArgumentParser(description="Resize GIF to any target dimensions")

    parser.add_argument("input", help="Input GIF file path")
    parser.add_argument("--output", "-o", help="Output GIF file path (default: input_WxH.gif)")
    parser.add_argument("--width", "-W", type=int, required=True, help="Target width in pixels")
    parser.add_argument("--height", "-H", type=int, required=True, help="Target height in pixels")

    args = parser.parse_args()

    if not os.path.exists(args.input):
        print(f"Error: Input file not found: {args.input}")
        sys.exit(1)

    if args.output:
        output_gif = args.output
    else:
        base = os.path.splitext(args.input)[0]
        output_gif = f"{base}_{args.width}x{args.height}.gif"

    resize_gif(args.input, output_gif, args.width, args.height)


if __name__ == "__main__":
    main()
