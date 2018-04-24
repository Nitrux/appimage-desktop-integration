# Appimage Desktop Integration Tools [![Build Status](https://travis-ci.org/nomad-desktop/appimage-desktop-integration.svg?branch=master)](https://travis-ci.org/nomad-desktop/appimage-desktop-integration)

Optional set of tools to assist users at verifying, activating, deploying and removing applications packaged as AppImage.


## Premise:
- AppImage applications _trust_ is defined by the presence (or not) of the executable bit.
- A **non-executable** AppImage file is an _untrusted_ (read: potentially dangerous) application. It should only be executed by a sandboxing utility (for example firejail).
- An executable AppImage file is (with explicit permission from the user) a _trusted_ and safe application.
- AppImage applications desktop integration is defined by the location of the file in `<XDG_USER_HOME>/Applications` or
`/opt/Applications`. Such applications will be considered as "deployed". This means that it will be added to the desktop 
menu by coping its ".Desktop" file and icon to their respective XDG locations.
- An AppImage file in `<XDG_USER_HOME>/Applications` is available only for the current user.
- An AppImage file in `/opt/Applications` is available for all users.
- A **non-executable** AppImage file in` <XDG_USER_HOME>/Applications` or `/opt/Applications` is still considered _untrusted_ its ".Desktop" file will be deployed but it must be modified to execute the application inside a sandboxing utility.


## Workflow
A. Executing an AppImage:
   1. Download a binary file.
   2. Open it in your file browser (or in the terminal with `xdg-open`).
   3. Wait for the signature verification to be completed.
   4. Click _Trust_.
   5. Click _Run_.

B. Executing an AppImage in sandbox:
   1. Download binary file.
   2. Open it in your file browser (or in the terminal with `xdg-open`)
   3. Wait for the signature verification to be completed.
   5. Click _Run in Sandbox_.
  
C. Deploy AppImage (using the first run utility):
   1. Download binary file.
   2. Open it in your file browser (or in the terminal with `xdg-open`)
   3. Wait for the signature verification to be completed.
   5. Click _Deploy_.
   
D. Deploy AppImage (using the Applications dir):
   1. Download binary file.
   2. Copy it to `<XDG_USER_HOME>/Applications`.
   3. Wait for the signature verification to be completed.

E. Remove AppImage
   1. Remoge AppImage file.


## AppImage First Run

This aims to ease the verification and integration of newly downloaded appimages. The user is warned about the danger of using unreliable binaries. It allows to:

- To deploy the applications .desktop file and icons.
- To test the application by executing it once.
- To trust (set executable permission to the file)

![appimagekitr](https://raw.githubusercontent.com/azubieta/appimage-desktop-integration/screenshots/screenshots/first_run_unsecure_appimage.png)


## User Applications Monitor

This aims to allow simple integration of appimages by monitoring a "desktop integrated" `Applications` folder, where 
the users can just copy the applications that they'd want and have them available from start menus and as mime-type handlers.

## AppImage Desktop Integration configuration UI

Provides a simple interface to deploy and monitor the mentioned tools.

![appimagekitr](https://github.com/azubieta/appimage-desktop-integration/blob/screenshots/screenshots/config.png?raw=true)

# Issues
If you find problems with the contents of this repository please create an issue.

©2018 Nitrux Latinoamericana S.C.
