# 100KBBH: 100kb Bullet Hell Game


![Language](https://img.shields.io/badge/language-C++%2017-9B599A.svg?style=flat-square)
![GitHub license](https://img.shields.io/github/license/EterDelta/100KBBH.svg?style=flat-square)

100KBBH is a minimalistic, yet stylized and addictive bullet hell game for Windows. As the name implies, the entire game takes up less than 100 kilobytes of space and is built entirely from scratch, without using any form of compression.

## Installation
The whole game compiles to a single executable. You can download a build from the Itch.io page, all the instructions, requirements and details can be found there. Alternatively, you can easily build it from the source.

## Building
This project uses Meson as its build system. Assuming you have Meson and Ninja installed on your machine, follow the steps below to build the project:

1. Clone the repository and navigate into the project's root directory.
2. Configure the project in a folder with Meson by running `meson setup --buildtype=release build-release` or `meson setup --buildtype=debugoptimized build-debug`.
3. Navigate to the configured folder and compile normally with `meson compile`.

Remember to edit the meson.build and `--reconfigure` the folders if you add or remove resources, as this project depends on a custom command for packing them.

For more detailed instructions and help, please refer to the [Meson documentation](https://mesonbuild.com/).