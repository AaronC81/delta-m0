#!/usr/bin/env python3

import fontforge, sys, subprocess, os

CHARACTERS = list("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM") + \
  ["space", "comma"]

for character in CHARACTERS:
  font = fontforge.open("/usr/share/fonts/noto/NotoSans-Regular.ttf")
  
  output_path = f"{os.path.dirname(os.path.abspath(__file__))}/graphics/font_h12_{character}.png"
  font[character].export(output_path, 12)
  subprocess.check_output([
    "convert", output_path,
    "-extent", "x16", "-color-threshold", "#000-#777", "-negate",
    output_path,
  ])
