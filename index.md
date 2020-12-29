
## important QT links:
download: http://download.qt.io/official_releases/qt/5.12/5.12.9/submodules/
list of examples: https://doc.qt.io/qt-5/qtexamples.html
used example: $HOME/Downloads/qtbase-everywhere-src-5.12.10/examples/vulkan/hellovulkanwidget

## Build on mac OS
Blog Post about Vulkan support in QT under mac OS: https://www.qt.io/blog/2018/05/30/vulkan-for-qt-on-macos
(https://forum.qt.io/topic/104553/vulkan-on-macos)

#### Install the QT Designer
install QT Designer for form editing from mac ports:
```
sudo port install qt513-qttools
```

#### Install MoltenVK
Install the Vulkan SDK for mac OS (MoltenVK) which can be downloaded from https://vulkan.lunarg.com/

```
cd external
curl 'https://sdk.lunarg.com/sdk/download/1.2.162.0/mac/vulkansdk-macos-1.2.162.0.dmg' > vulkansdk-macos-1.2.162.0.dmg
```

The next commands basically copies the header and dynamic libraries to `/usr/local/` and some demo applications to `/Applications/`. The line which copies the directory `MoltenVK` from the Image to the project directory `external` is needed because the script `./install_vulkan.py` installs the MoltonVK libraries (e.g. `libMoltenVK.dylib`) in `/usr/local` but not the header files (e.g. `<MoltenVK/mvk_vulkan.h>`). However, the QT Vulkan-Window-Cocoa base classes requires this Classes.
```
hdiutil attach vulkansdk-macos-1.2.162.0.dmg
cp -r /Volumes/vulkansdk-macos-1.2.162.0/MoltenVK ./
/bin/bash

cd /Volumes/vulkansdk-macos-1.2.162.0/
./install_vulkan.py

exit

hdiutil detach /Volumes/vulkansdk-macos-1.2.162.0/
```
If an older version is already in place, use `./install_vulkan.py --force-install` to override the existing version.


#### Build QT5

download and extract QT
```
cd external
#curl 'http://download.qt.io/official_releases/qt/5.15/5.15.2/submodules/qtbase-everywhere-src-5.15.2.tar.xz' --location > qtbase-everywhere-src-5.15.2.tar.xz
curl 'http://download.qt.io/official_releases/qt/5.12/5.12.10/submodules/qtbase-everywhere-src-5.12.10.tar.xz'  --location > qtbase-everywhere-src-5.12.10.tar.xz
tar xvzf qtbase-everywhere-src-5.12.10.tar.xz
cd qtbase-everywhere-src-5.12.10
```

patch for mac OS 10.13 (should not be required for newer mac OS versions, see https://bugreports.qt.io/browse/QTBUG-76777).
```
patch -p2 < ../qcore_for_sdk_10_13_1.patch
```

build QT:
```
./configure -opensource -confirm-license -developer-build -I /usr/local/include/ -I "$(pwd)/../MoltenVK/include/" -feature-vulkan -v -skip qtwebengine
time make
# make install
```
more infos can be found on: https://doc.qt.io/qt-5/macos-building.html

../qt5/configure -developer-build -skip qtquick3d -skip qtwebengine -opensource -nomake examples -nomake tests -confirm-license -vulkan -I $VULKAN_SDK/../MoltenVK/include -L $VULKAN_SDK/lib
from https://stackoverflow.com/questions/60466377/qt-5-14-0-vulkan-under-qml-causes-stdsystem-error-mutex-lock-failed
