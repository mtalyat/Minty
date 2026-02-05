# <image src="https://raw.githubusercontent.com/mtalyat/Minty/refs/heads/main/Images/Icon.png" width=24> Minty <image src="https://raw.githubusercontent.com/mtalyat/Minty/refs/heads/main/Images/Icon.png" width=24>
This is the official repository for the Minty game engine.

If you would like more information about the engine, such as features, software architecture, and more: check out the [wiki](https://github.com/mtalyat/Minty/wiki) page.

## <image src="https://raw.githubusercontent.com/mtalyat/Minty/refs/heads/main/Images/Mint.png" width=16> Building <image src="https://raw.githubusercontent.com/mtalyat/Minty/refs/heads/main/Images/Mint.png" width=16>

### Prerequisites

This is a list of things you must have installed prior to building the Minty engine.

#### **[Vulkan SDK](https://www.lunarg.com/vulkan-sdk/)**

Version 1.3. The Vulkan Software Development Kit is used for the rendering backend. You do not need to use Vulkan to use the engine- but the engine needs to use it!

#### **[CMake](https://cmake.org/download/)**

Latest release is sufficient. CMake is used for building the engine and any games/projects made with it. Of course, you do not have to use CMake, but CMake is already set up for you. CMake also requires you to have a compiler installed, such as Visual Studio (MSVC) or gcc.

#### **[Python](https://www.python.org/downloads/)**

Latest release should work. Latest version tested is Python 3.13.0. Python is used for some building and project management scripts. It makes life easier.

### <image src="https://raw.githubusercontent.com/mtalyat/Minty/refs/heads/main/Images/Mint.png" width=16> Quick Installation <image src="https://raw.githubusercontent.com/mtalyat/Minty/refs/heads/main/Images/Mint.png" width=16>

To install:

1. Clone this repository. [Don't know how?](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository)
2. Run `installer.bat install`.

To uninstall:
1. Run `installer.bat uninstall`.
2. Delete the repository.

If you do not want to run the installer, all you must do to "install" Minty is to create an environment variable called `MINTY_PATH` that points to the directory you check out the repository to.

### <image src="https://raw.githubusercontent.com/mtalyat/Minty/refs/heads/main/Images/Mint.png" width=16> Documentation <image src="https://raw.githubusercontent.com/mtalyat/Minty/refs/heads/main/Images/Mint.png" width=16>

All public code is commented using Javadoc style comments. High-level design choices can be found in the [Minty Wiki](https://github.com/mtalyat/Minty/wiki).