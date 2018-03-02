#!/usr/bin/env bash

build_scripts_dir=`dirname $0`
source_dir=`dirname $build_scripts_dir`

make DESTDIR="appdir" -j$(nproc) install
find appdir/

rsvg-convert -f png -h 256 -w 256 ${source_dir}/res/images/appimage.svg > appdir/usr/appimage.png

wget -c -nv "https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage" -O linuxdeployqt-continuous-x86_64.AppImage
chmod a+x linuxdeployqt-continuous-x86_64.AppImage


unset QTDIR; unset QT_PLUGIN_PATH ; unset LD_LIBRARY_PATH
export VERSION=$(git rev-parse --short HEAD) # linuxdeployqt uses this for naming the file

FIRST_RUN_DESKTOP_FILE=$(find appdir/usr/ -iname '*first*run*.desktop')
./linuxdeployqt-continuous-x86_64.AppImage ${FIRST_RUN_DESKTOP_FILE} -bundle-non-qt-libs -appimage