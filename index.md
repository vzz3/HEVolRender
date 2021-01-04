
## important QT links:
download: http://download.qt.io/official_releases/qt/5.12/5.12.9/submodules/
list of examples: https://doc.qt.io/qt-5/qtexamples.html
used example: $HOME/Downloads/qtbase-everywhere-src-5.12.10/examples/vulkan/hellovulkanwidget

## important Vulkan links
vulkan low level API explanation: https://software.intel.com/content/www/us/en/develop/articles/api-without-secrets-introduction-to-vulkan-part-1.html
examples: https://github.com/KhronosGroup/Vulkan-Samples
https://developer.nvidia.com/blog/vulkan-dos-donts/

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
patch -p2 < ../qt_patches/qcore_for_sdk_10_13_1.patch
```

patch for the QT versions before 5.15.0 Beta2 https://bugreports.qt.io/browse/QTBUG-82600
* Do not constantly create new surfaces with MoltenVK on macOS (`7b86168.diff`): https://codereview.qt-project.org/c/qt/qtbase/+/292567
* macOS: MoltenVK: Pass in the layer instead of the view (`23fd7bd.diff`): https://codereview.qt-project.org/c/qt/qtbase/+/292568

* Posible warning from MoltenVK:
> vkCreateMacOSSurfaceMVK(): You are not calling this function from the main thread. NSView should only be accessed from the main thread. When using this function outside the main thread, consider passing the CAMetalLayer itself in VkMacOSSurfaceCreateInfoMVK::pView, instead of the NSView.

* Error from NSView:
> libc++abi.dylib: terminating with uncaught exception of type std::__1::system_error: mutex lock failed: Invalid argument

* Exceptions on `void QVulkanWindowPrivate::init()` line `vkGetPhysicalDeviceSurfaceFormatsKHR(physDev, surface, &formatCount, nullptr);`
> Thread 1: EXC_BAD_ACCESS (code=1, address=0x4fffffffc)

* or, if the VK layer `VK_LAYER_KHRONOS_validation` is enabled
> vkDebug: Validation: 0: Validation Error: [ VUID-vkGetPhysicalDeviceSurfaceFormatsKHR-surface-parameter ] Object 0: VK_NULL_HANDLE, type = VK_OBJECT_TYPE_INSTANCE; | MessageID = 0xf36628f4 | Invalid VkSurfaceKHR Object 0x20000000002. The Vulkan spec states: surface must be a valid VkSurfaceKHR handle (https://vulkan.lunarg.com/doc/view/1.2.162.0/mac/1.2-extensions/vkspec.html#VUID-vkGetPhysicalDeviceSurfaceFormatsKHR-surface-parameter)
2021-01-02 21:56:42.129550+0100 ppvr_vulkan[63094:2863037] vkDebug: Validation: 0: Validation Error: [ UNASSIGNED-Threading-Info ] Object 0: handle = 0x20000000002, type = VK_OBJECT_TYPE_SURFACE_KHR; | MessageID = 0x5d6b67e2 | Couldn't find VkSurfaceKHR Object 0x20000000002. This should not happen and may indicate a bug in the application.


```
patch -p1 < ../qt_patches/7b86168.diff
patch -p1 < ../qt_patches/23fd7bd.diff
	# stdout: Hunk #1 succeeded at 80 (offset -1 lines).
```






build QT:
```
./configure -opensource -confirm-license -developer-build -I /usr/local/include/ -I "$(pwd)/../MoltenVK/include/" -feature-vulkan -v -skip qtwebengine
time make
# make install
```
more infos can be found on: https://doc.qt.io/qt-5/macos-building.html
<!--
../qt5/configure -developer-build -skip qtquick3d -skip qtwebengine -opensource -nomake examples -nomake tests -confirm-license -vulkan -I $VULKAN_SDK/../MoltenVK/include -L $VULKAN_SDK/lib
from https://stackoverflow.com/questions/60466377/qt-5-14-0-vulkan-under-qml-causes-stdsystem-error-mutex-lock-failed
-->

## Debug Mac OS
### QT
Set the environment variable `DYLD_IMAGE_SUFFIX=_debug` (Xcode -> menu Product-> Scheme -> Run -> Arguments -> Environment Variables). This loads the _debug binaries from the framework folders (e.g.: `external/qtbase-everywhere-src-5.12.10/lib/QtCore.framework/QtCore_debug`). https://doc.qt.io/qt-5/debug.html

### MoltonVK
Set the environment variable `MVK_LOG_LEVEL_INFO`
