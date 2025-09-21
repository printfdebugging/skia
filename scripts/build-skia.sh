#!/bin/bash

mkdir -p libs && cd libs || exit
git clone 'https://chromium.googlesource.com/chromium/tools/depot_tools.git'
export PATH="/home/printfdebugging/downloads/skia/depot_tools:${PATH}"
ensure_bootstrap

git clone https://skia.googlesource.com/skia.git

(
	cd skia || exit
	python3 tools/git-sync-deps
	python3 bin/fetch-ninja
)

(

	export PATH="/home/printfdebugging/downloads/skia/depot_tools:${PATH}"
	cd skia || exit
	gn gen out/Shared --args='is_official_build=false is_component_build=true'
	bear -- ninja -C out/Shared
)
