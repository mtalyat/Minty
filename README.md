<image src="https://github.com/mtalyat/Minty/blob/main/Images/Icon.png" alt="The Minty engine logo." width=200>

# Minty
This is the official repository for the Minty game engine.

If you would like more information about the engine, such as features, software architecture, and more: check out the [wiki](https://github.com/mtalyat/Minty/wiki) page.

## Building

### Prerequisites

This is a list of things you must have installed prior to building the Minty engine.

**[Vulkan SDK](https://www.lunarg.com/vulkan-sdk/)**

Version 1.3. The Vulkan Software Development Kit is used for the rendering backend. You do not need to use Vulkan to use the engine- but the engine needs to use it!

**[Doxygen](https://www.doxygen.nl/download.html)**

This is only needed if you would like to [generate the documentation](#documentation) for the Minty source code.

### Quick Installation

To install:

1. Clone this repository. [Don't know how?](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository)
2. Run `installer.bat`.
3. Build the Minty source code at `MINTY_PATH/Minty/Source/`.

To uninstall:
1. Run `uninstaller.bat`.
2. Delete the repository.

### Documentation

1. Open the `MINTY_PATH/Minty` directory.
2. Run `generate_documentation.bat`.
