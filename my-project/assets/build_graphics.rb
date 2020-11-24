#!/usr/bin/env ruby
require 'rmagick'

header_results = File.open("#{__dir__}/graphics.h", 'w')
header_results.puts "#pragma once"
header_results.puts "#include <stdint.h>"
header_results.puts

source_results = File.open("#{__dir__}/graphics.c", 'w')
source_results.puts "#include \"graphics.h\""

image_files = Dir["#{__dir__}/graphics/*.png"]

image_files.each do |image_file|
  image = Magick::Image.read(image_file).first

  # Build an array of pixels
  pixels = Array.new(image.columns) { Array.new(image.rows) { nil } }
  image.each_pixel do |pixel, col, row|
    pixels[col][row] = (pixel.intensity == 0)
  end

  # Create sprite data
  bytes = []
  raise 'sprite height is not divisible by 8' unless image.rows % 8 == 0
  pages = image.rows / 8
  pages.times do |page|
    image.columns.times do |col|
      bytes << 8.times.map { |i| pixels[col][page * 8 + i] ? '1' : '0' }.join.to_i(2)
    end
  end

  name = "graphics_#{File.basename(image_file, '.png')}"
  hex_bytes = [image.columns, pages, *bytes].map { |b| "0x#{b.to_s(16)}" }.join(', ')
  header_results.puts "extern const uint8_t #{name}[#{hex_bytes.length}];"
  source_results.puts "const uint8_t #{name}[] = { #{hex_bytes} };"
end
