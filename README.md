# 100KBBH: 100kb Bullet Hell Game


![Language](https://img.shields.io/badge/language-C++%2017-9B599A.svg?style=flat-square)
![GitHub license](https://img.shields.io/github/license/EterDelta/100KBBH?style=flat-square)

100KBBH is a minimalistic, yet stylized and addictive bullet hell game for Windows. As the name implies, the entire game takes up less than 100 kilobytes of space and is built entirely from scratch, without using any form of compression.

## Installation
The whole game compiles to a single executable. You can download a build from the [Itch.io page](https://eterdelta.itch.io/100kbbh), all the instructions, requirements and details can be found there. Alternatively, you can easily build it from the source.

## Building
This project uses CMake as its build system. Assuming you have CMake and a compatible compiler (like Visual Studio) installed on your Windows machine, follow the steps below to build the project:

1. Clone the repository and navigate into the project's root directory.
2. Configure the project using CMake by running `cmake -S . -B build`.
3. Compile the project with `cmake --build build --config Release` or `cmake --build build --config Debug`.

Remember to edit the CMakeLists.txt and re-run CMake if you add or remove resources.

For more detailed instructions and help, please refer to the [CMake documentation](https://cmake.org/documentation/).