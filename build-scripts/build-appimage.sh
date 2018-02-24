#!/usr/bin/env bash

build_scripts_dir=`dirname $0`
source_dir=`dirname $build_scripts_dir`

mkdir -p appimage-desktop-integration/DEBIAN
make DESTDIR="appimage-desktop-integration/" -j $(nproc) install

echo "
Package: appimage-desktop-integration
Architecture: amd64
Maintainer: Luis Lavaire
Depends: 
Priority: optional
Version: 0.1
Description: AppImage integration with the desktop.
" > appimage-desktop-integration/DEBIAN/control

chown -R root:root appimage-desktop-integration/

dpkg-deb --build deb/
