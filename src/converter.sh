for f in frame_*.png; do
  ~/Desktop/projects/zephyrproject/modules/lib/gui/lvgl/scripts/LVGLImage.py "$f" --cf I1 --ofmt C -o img_out
done

``