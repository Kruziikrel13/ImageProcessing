#!/usr/bin/env bash

PICTURES="pictures/"
OUTPUT="output"

operations=(
  "-reverse"
  "-brightness 40"
  "-contrast 40"
  "-rgb2grey 80"
  "-grey2rgb"
  "-rgb2bw"
  "-rgb2sepia"
  "-rotate -left"
  "-rotate -right"
  "-zoom"
  "-scale 20"
  "-blur 90"
)

for op in "${operations[@]}"; do
  op_dir="$OUTPUT/${op//[ -]/}"
  mkdir -p "$op_dir"
  perf record --output="$op_dir/profile.data" \
    -g --call-graph=dwarf -- ./build/serial "$PICTURES" "$op_dir/" $op
done
