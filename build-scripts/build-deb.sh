#! /bin/sh

mv appdir appimage-desktop-integration
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
