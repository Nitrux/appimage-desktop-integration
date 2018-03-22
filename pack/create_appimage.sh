#!/usr/bin/env bash

build_scripts_dir=`dirname $0`
source_dir=`dirname $build_scripts_dir`

DESTDIR=appdir make install
cp ${source_dir}/res/images/appimage.svg appdir

patchelf --set-rpath '$ORIGIN/../lib/' appdir/usr/bin/appimage_first_run
patchelf --set-rpath '$ORIGIN/../lib/' appdir/usr/bin/user_apps_monitor

wget -c -nv "https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage"
chmod a+x linuxdeployqt-continuous-x86_64.AppImage

unset QTDIR; unset QT_PLUGIN_PATH ; unset LD_LIBRARY_PATH

export VERSION=$(git rev-parse --short HEAD) # linuxdeployqt uses this for naming the file

./linuxdeployqt-continuous-x86_64.AppImage appdir/usr/share/applications/org.appimage.desktop-integration-tool.desktop -bundle-non-qt-libs -appimage
