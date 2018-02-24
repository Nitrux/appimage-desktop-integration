#!/usr/bin/env bash

build_scripts_dir=`dirname $0`
source_dir=`dirname $build_scripts_dir`

make DESTDIR="appimage-desktop-integration" -j$(nproc) install
find appimage-desktop-integration/


# Build a Debian Binary.

mkdir -p appimage-desktop-integration/DEBIAN

echo "
Package: appimage-desktop-integration
Architecture: amd64
Maintainer: Luis Lavaire
Depends: qt5
Priority: optional
Version: 0.1
Description: AppImage integration with the desktop.
" > appimage-desktop-integration/DEBIAN/control

chown -R root:root appimage-desktop-integration/
dpkg-deb --build appimage-desktop-integration/


# Build an AppImage.

mv appimage-desktop-integration appdir

rsvg-convert -f png -h 256 -w 256 ${source_dir}/res/images/appimage.svg > appdir/appimage.png

wget -c -nv "https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage" -O linuxdeployqt-continuous-x86_64.AppImage
chmod a+x linuxdeployqt-continuous-x86_64.AppImage

unset QTDIR; unset QT_PLUGIN_PATH ; unset LD_LIBRARY_PATH
export VERSION=$(git rev-parse --short HEAD) # linuxdeployqt uses this for naming the file

FIRST_RUN_DESKTOP_FILE=$(find appdir/usr/ -iname '*first*run*.desktop')
appimage-wrapper ./linuxdeployqt-continuous-x86_64.AppImage ${FIRST_RUN_DESKTOP_FILE} -bundle-non-qt-libs -appimage
