#!/usr/bin/env bash

BACKENDS="skia-backend"

if [ "$1" == "" ]; then
  BACKENDS="skia-backend"
elif [ "$1" == "skia" ]; then
  BACKENDS="skia-backend"
elif [ "$1" == "cairo" ]; then
  BACKENDS="cairo-backend"
fi

cd ../Build/src/resvg/capi
export SKIA_DIR=$(PWD)/../../skia
export SKIA_LIB_DIR=$(PWD)/../../../mac/lib
export MACOSX_DEPLOYMENT_TARGET=10.9

if [ -d .cargo ]; then
  rm -r .cargo
fi

echo ---------------------------------
mkdir .cargo
echo [build] > .cargo/config
if [ "$BACKENDS" == "skia-backend" ]; then
  echo rustflags = [\"-L$SKIA_LIB_DIR\", \"-lframework=Metal\", \"-lframework=Foundation\"] >> .cargo/config
elif [ "$BACKENDS" == "cairo-backend" ]; then
  echo rustflags = [\"-ldylib=pixman-1\", \"-lframework=Foundation\"] >> .cargo/config
fi

cargo build --verbose --release --features $BACKENDS
cd ..

mv target/release/libresvg.a ../../mac/lib