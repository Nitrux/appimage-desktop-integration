# Appimage Desktop Integration Tools
Optional set of tools to assist users at verifying, activating, installing and removing applications packed as appimage.


## Premises:
- Appimage applications user trust is defined by the presence (or not) of the executable bit.
- A non executable appimage file is an untrusted (potentially dangerous) application. Should only by executed by a 
sandboxing utility (by example firejail).
- An executable appimage file is (whit explicit concern of the user) a trusted and safe application.

- Appimage applications desktop integration is defined by the location of the file in <XDG_USER_HOME>/Applications or
/opt/Applications. Such applications will be considered as "deployed". This means that must be included in the desktop 
menu by coping its ".Desktop" file and icon to their respective XDG locations.
- An appimage file in <XDG_USER_HOME>/Applications is available only for the current user.
- An appimage file in /opt/Applications is available for all users.
- A non executable appimage file in <XDG_USER_HOME>/Applications or /opt/Applications is still considered untrusted. Its
".Desktop" file will be deployed but must be modified to execute the application inside a sandboxing utility.


## Workflows
1. Execute an appimage:
   1. Download binary file.
   2. Open it in your file browser (or in the terminal by means of xdg-open)
   3. Wait for the signature verification to be completed
   4. Click Trust
   5. Click Run

2. Execute an appimage in sandbox:
   1. Download binary file.
   2. Open it in your file browser (or in the terminal by means of xdg-open)
   3. Wait for the signature verification to be completed
   5. Click Run in sandbox
  
3. Deploy appimage (using the first run utility):
   1. Download binary file.
   2. Open it in your file browser (or in the terminal by means of xdg-open)
   3. Wait for the signature verification to be completed
   5. Click Deploy
   
3. Deploy appimage (using the Applications dir):
   1. Download binary file.
   2. Copy it to <XDG_USER_HOME>/Applications
   3. Wait for the signature verification to be completed

4. Remove appimage
   1. Remoge appimage file.


## Appimage First Run

Aims to ease the verification and integration of newly downloaded appimages.
The user is warned about the danger of using unreliable binaries.
It allows:
- To deploy the applications .desktop file and icons.
- To test the application by executing it once.
- To trust (set executable permission to the file)

![appimagekitr](https://raw.githubusercontent.com/azubieta/appimage-desktop-integration/screenshots/screenshots/first_run_unsecure_appimage.png)


## User Applications Monitor

Aims to allow simple integration of appimages by monitoring a "desktop integrated" Applications dir, where 
the user can just copy the applications that she/he want to have available from menus and as mime-type handler. 