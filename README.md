# HEVolRender
This is a GPU implementation of the homomorphic-encrypted X-ray rendering approach that we presented at the [IEEE VIS 2020](https://doi.org/10.1109/TVCG.2020.3030436).


# Build Project
## Build on mac OS
Blog Post about Vulkan support in QT under mac OS: https://www.qt.io/blog/2018/05/30/vulkan-for-qt-on-macos
(https://forum.qt.io/topic/104553/vulkan-on-macos)

### Clone the Repository
```
git clone --recurse-submodules ssh://$DOMAIN\\$USER@$HOST/~/git/HEVolRender-Cpp.git
cd HEVolRender-Cpp.git
```

### Install the QT Designer
Install the QT Designer for form editing of UI files, from mac ports:
```
sudo port install qt513-qttools
```

### Install MoltenVK
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
cd ..
```
If an older version is already in place, use `./install_vulkan.py --force-install` to override the existing version.

### Build QT5
More infos about build QT from source on macOS can be found at: https://doc.qt.io/qt-5/macos-building.html .
<!--
../qt5/configure -developer-build -skip qtquick3d -skip qtwebengine -opensource -nomake examples -nomake tests -confirm-license -vulkan -I $VULKAN_SDK/../MoltenVK/include -L $VULKAN_SDK/lib
from https://stackoverflow.com/questions/60466377/qt-5-14-0-vulkan-under-qml-causes-stdsystem-error-mutex-lock-failed
-->

#### Build QT 5.12.10 for macOS 10.13
Download and extract QT:
```
cd external
curl 'http://download.qt.io/official_releases/qt/5.12/5.12.10/submodules/qtbase-everywhere-src-5.12.10.tar.xz'  --location > qtbase-everywhere-src-5.12.10.tar.xz
tar xvzf qtbase-everywhere-src-5.12.10.tar.xz
cd qtbase-everywhere-src-5.12.10
```

Apply patch for mac OS 10.13 (should not be required for newer mac OS versions, see https://bugreports.qt.io/browse/QTBUG-76777).
```
patch -p2 < ../qt_patches/qcore_for_sdk_10_13_1.patch
```

Apply patch for the QT versions before 5.15.0 Beta2 https://bugreports.qt.io/browse/QTBUG-82600
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

Compile QT:
```
./configure -opensource -confirm-license -developer-build -I /usr/local/include/ -I "$(pwd)/../MoltenVK/include/" -feature-vulkan -v -skip qtwebengine
time make
# use 20 cores for the build:
	time make -j 20
# make install
cd ../
```

Make a symlink to the compiled QT version. CMake need this in order to find the QT version we have just compiled.
```
ln -s qtbase-everywhere-src-5.12.10 qtbase-everywhere-src-5
cd ../
```

#### Build QT 5.15.10 for macOS 10.15
Download and extract QT:
```
cd external
curl 'http://download.qt.io/official_releases/qt/5.15/5.15.2/submodules/qtbase-everywhere-src-5.15.2.tar.xz' --location > qtbase-everywhere-src-5.15.2.tar.xz
tar xvzf qtbase-everywhere-src-5.15.2.tar.xz
cd qtbase-everywhere-src-5.15.2
```

Compile QT:
```
./configure -opensource -confirm-license -developer-build -I /usr/local/include/ -I "$(pwd)/../MoltenVK/include/" -feature-vulkan -v -skip qtwebengine
time make
# use 20 cores for the build:
	time make -j 20
# make install
cd ../
```

Make a symlink to the compiled QT version. CMake need this in order to find the QT version we have just compiled.
```
ln -s qtbase-everywhere-src-5.15.2 qtbase-everywhere-src-5
cd ../
```

### Create Xcode project for HEVolRender

```
mkdir build
cd build
cmake -G Xcode ../
```


### Debugging on Mac OS
#### Use QT Framework Version with Debug Symbols
Set the environment variable `DYLD_IMAGE_SUFFIX=_debug` (Xcode -> menu Product-> Scheme -> Run -> Arguments -> Environment Variables). This loads the _debug binaries from the framework folders (e.g.: `external/qtbase-everywhere-src-5.12.10/lib/QtCore.framework/QtCore_debug`). https://doc.qt.io/qt-5/debug.html

#### Enable MoltonVK Debug Outputs
Set the environment variable `MVK_LOG_LEVEL_INFO`.




## Build on Linux (Ubuntu 20.4)
Install required software build tools and system library headers with *apt*:
```
apt install vulkan-tools git cmake build-essential libglu1-mesa-dev '^libxcb.*-dev' libx11-xcb-dev libxkbcommon-dev libxkbcommon-x11-dev libfontconfig-dev
	# libxrender-dev libxi-dev libvulkan-dev curl
```

Clone the git repository:
```
git clone --recurse-submodules ssh://$DOMAIN\\$USER@$HOST/~/git/HEVolRender-Cpp.git
	# for already cloned repositories
	git submodule update --init --recursive
```

Install Vulkan SDK (see https://vulkan.lunarg.com/sdk/home#linux)
```
wget -qO - https://packages.lunarg.com/lunarg-signing-key-pub.asc | sudo apt-key add -
sudo wget -qO /etc/apt/sources.list.d/lunarg-vulkan-1.2.162-focal.list https://packages.lunarg.com/vulkan/1.2.162/lunarg-vulkan-1.2.162-focal.list
sudo apt update
sudo apt install vulkan-sdk
```

#### Build QT5
More infos about build QT from source on Linux can be found at: https://wiki.qt.io/Building_Qt_5_from_Git

Download and extract QT
```
cd HEVolRender-Cpp/external
curl 'http://download.qt.io/official_releases/qt/5.12/5.12.10/submodules/qtbase-everywhere-src-5.12.10.tar.xz' --location > qtbase-everywhere-src-5.12.10.tar.xz
tar xvf qtbase-everywhere-src-5.12.10.tar.xz
cd qtbase-everywhere-src-5.12.10
```

Compile QT:
```
./configure -opensource -confirm-license -developer-build -feature-vulkan -xcb -fontconfig -v -skip qtwebengine
	# -recheck-all
time make
# use 20 cores for the build:
	time make -j 20
# make install
cd ../
```

Make a symlink to the compiled QT version. CMake need this in order to find the QT version we have just compiled.
```
ln -s qtbase-everywhere-src-5.12.10 qtbase-everywhere-src-5
cd ../
```

### build HEVolRender

```
mkdir build
cd build
cmake ../
make
```


# GPU Shader timeout
## Linux
### NVIDIA GPU Shader timeout
Just add Option "Interactive" "0" to the device section of your GPU. [https://stackoverflow.com/questions/6906579/cuda-visual-profiler-interactive-x-config-option]
In my Case the Device ins configured in `/usr/share/X11/xorg.conf.d/100-nvidia-rtx3090.conf`.
Example:
> ```
Section "Device"
    Identifier     "Device1"
    Driver         "nvidia"
    VendorName     "NVIDIA Corporation"
    BoardName      "GeForce RTX 3090"
    BusID          "PCI:23:0:0"
	Option         "Interactive" "0"
EndSection
>```

Than you need to restart the `/usr/lib/xorg/Xorg` process (I killed it `kill -9 PID_OF_XORG`).

If you do not have a X11 config for your GPU, you can create one with `X`.
Create X11 / Xorg Config options for GPU 1:
```
X :1 -configure
```


### AMD GPU  Shader Timeout
From `/var/log/syslog`:
> [  383.497475] [drm:amdgpu_job_timedout [amdgpu]] *ERROR* ring gfx timeout, but soft recovered

https://01.org/linuxgraphics/gfx-docs/drm/gpu/amdgpu.html
lockup_timeout

To change the timeout to 60sec the kernel parameter `amdgpu.lockup_timeout=60000` need to be set.
```
nano /etc/default/grub
```

example content:
> ```
> # For full documentation of the options in this file, see:
> #   info -f grub -n 'Simple configuration'
>
> GRUB_DEFAULT=0
> GRUB_TIMEOUT_STYLE=hidden
> GRUB_TIMEOUT=0
> GRUB_DISTRIBUTOR=`lsb_release -i -s 2> /dev/null || echo Debian`
> GRUB_CMDLINE_LINUX_DEFAULT="quiet splash amdgpu.lockup_timeout=60000"
> GRUB_CMDLINE_LINUX=""
> ```

Run `update-grub` afterwards to update.


# Important Configurations
#### Machine Word Length
See pre compiler constant `_BIG_INT_WORD_LENGTH_PRESET_` in *src/math/BigInt_wordDef.h* and *res/shaders/math/bigInt_defs.h.glsl*. The value for the CPU (C++) und GPU (GLS) need to be equal.

#### Configure multiplication Algorithm
The configuration for the CPU is in file *src/math/BigInt_wordDef.h* and the configuration for the GPU is done in *res/shaders/math/bigInt_defs.h.glsl*.
* `BIG_INT_FORCE_SCHOOL`: If defined the basic school algorithm will be used instead of the multiplication with the deferred carry propagation from Colin Plumb.
* `BIG_INT_REDUCE_BRANCHING`: Disables the checks that prevents unnecessary multiplications with zero.

#### Configure the Montgomery Reduction for Modular Exponentiation
The configuration for the CPU is in file *src/math/BigInt_wordDef.h* and the configuration for the GPU is done in *res/shaders/math/bigInt_defs.h.glsl*.
* `BIG_INT_NO_MONTGOMERY_REDUCTION`: If defined the classic division will be used for modulo reduction instead of the Montgomery reduction.
* `BIG_INT_MONTGOMERY_FORCE_READABLE`: Uses a easily readable version of the Montgomery reduction. However, for long numbers this is not efficient.

#### Configure the Usage  Montgomery Reduction on the GPU
In order to enable the usage of Montgomery reduction for the encrypted X-Ray composition on the GPU the constant `GPU_MONTGOMERY_REDUCTION`  need to be defined. This is need to be done in the files *src/paillier/Paillier_typeDev.h* for the CPU and in the file  *res/shaders/math/bigInt_defs.h.glsl* for the GPU.
It need to be defined or remove in both files equally since the rendering with Montgomery reduction on the GPU requires that the encrypted volume data set is uploaded in Montgomery form by the CPU.

#### Public Key Length
The length of the Public Key Modulus that should be used for the encryption is defined by the pre compiler constant `PAILLIER_MODULUS_BIT_LENGTH`. The value defines the length in bits. The value of the constant for the CPU need to equal to the value on the GPU side. See the C++ file *src/paillier/Paillier_typeDev.h* and the GLSL file  *res/shaders/math/bigInt_defs.h.glsl*.


#### Other
For calculations with Paillier encrypted values on the CPU not only the fixed length big integer classe can be used but also the arbitrary length version. This can be achieved by commenting out the pre compiler constant `USE_FIX_WIDTH_INTEGER` in *src/paillier/Paillier_typeDev.h*.


# TODO
- modPow() for unsigned fixed length big-integers in C++ and GLSL (required for Paillier Multiplication)
- floating point numbers on GPU. Where to write the exponent? Z-Buffer?
- The PaillierMath.cpp unit test file bail out with an assertion error if build with g++ under ubuntu.


# References
## Important QT links:
- QT Download: http://download.qt.io/official_releases/qt/5.12/5.12.9/submodules/
- List of examples: https://doc.qt.io/qt-5/qtexamples.html
- Example I used as a base for this Project: $HOME/Downloads/qtbase-everywhere-src-5.12.10/examples/vulkan/hellovulkanwidget

## Important Vulkan links
- Vulkan low level API explanation: https://software.intel.com/content/www/us/en/develop/articles/api-without-secrets-introduction-to-vulkan-part-1.html
- Examples from KhronosGroup: https://github.com/KhronosGroup/Vulkan-Samples
- Headless example: https://github.com/SaschaWillems/Vulkan/tree/master/examples/renderheadless
- Vulkan Dos and Don???ts: https://developer.nvidia.com/blog/vulkan-dos-donts/
- Uniforms: https://github.com/nvpro-samples/gl_vk_threaded_cadscene/blob/master/doc/vulkan_uniforms.md
- Image and buffer format support on different Systems: http://vulkan.gpuinfo.org/listformats.php?platform=macos
- C++ to SIRV compiler: https://github.com/seanbaxter/shaders/blob/master/README.md
- SPIRV Debugger: https://github.com/dfranx/ShaderDebugger, https://github.com/dfranx/SPIRV-VM
- Vulkan Shader Debug Printf: https://vulkan.lunarg.com/doc/sdk/1.2.135.0/mac/debug_printf.html, https://vulkan.lunarg.com/issue/home?limit=10;q=;mine=false;org=false;khronos=false;lunarg=false;indie=false;status=new,open, https://github.com/KhronosGroup/Vulkan-ValidationLayers/blob/master/docs/debug_printf.md
