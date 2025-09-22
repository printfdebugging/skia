#!/bin/bash

# NOTE: run the script from the root of the project

project_dir=$(pwd)
skia_source=https://skia.googlesource.com/skia.git
depot_tools=https://chromium.googlesource.com/chromium/tools/depot_tools.git

# clone skia and build tools
mkdir -p libs
git clone "$depot_tools" "libs/depot_tools"
git clone "$skia_source" "libs/skia"

# set path and run the bootstrap script
export PATH="$project_dir/libs/depot_tools:${PATH}"
ensure_bootstrap

# sync git dependencies
cd "$project_dir/libs/skia" || exit
python3 tools/git-sync-deps
python3 bin/fetch-ninja

# build skia
gn gen out/Shared --args='is_official_build=false is_component_build=true'
bear -- ninja -C out/Shared
