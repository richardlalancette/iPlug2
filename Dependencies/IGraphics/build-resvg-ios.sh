#!/bin/sh

cd ../Build/src/resvg

rustup target add aarch64-apple-ios
export SKIA_DIR=$(PWD)/../skia
export SKIA_LIB_DIR=$(PWD)/../../ios/lib/arm64
export IPHONEOS_DEPLOYMENT_TARGET=12.0
cargo build --release --features "skia-backend"

cd capi

if [ -d .cargo ]; then
  rm -r .cargo
fi

echo ---------------------------------
mkdir .cargo
echo [build] > .cargo/config
echo rustflags = [\"-lframework=Metal\", \"-lframework=Foundation\"] >> .cargo/config

cargo build --verbose --release --features "skia-backend"
cd ..

mv target/release/libresvg.a ../../ios/lib/arm64