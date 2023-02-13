# Supercell Coding Test
Hi! This is the base code structure for the Supercell coding test.
The code below is a very basic and intensionally broken version of the class game [**PONG**](https://en.wikipedia.org/wiki/Pong).
## Info
This C++ code base is built using  [SFML](https://www.sfml-dev.org/index.php) and is configured to generate XCode and Visual Studio projects.
> The libraries for SFML are embedded in the repo so shouldn't require any further setup or downloading from the the SFML website.

[CMake](https://cmake.org/) version 3.22 or later is required to generate the projects.  
>The project is configured for a limited purpose (i.e. to generate an XCode or VS project easily).  It is not setup to build within CMake or be installed etc.

## How to generate project files

### Visual Studio 2022
One you have the project cloned to your PC.  Open a command prompt and from the source code directory run:
`cmake -B./build -G"Visual Studio 17 2022"`

Open `hive_test.sln` from `/build`

### Visual Studio 2019
One you have the project cloned to your PC.  Open a command prompt and from the source code directory run:
`cmake -B./build -G"Visual Studio 16 2019"`

Open `hive_test.sln` from `/build`

### XCode
One you have the project cloned to your MAC.  Open a terminal and from the source code directory run:
`cmake -B./build -GXcode`

Open `hive_test.xcodeproj` from `/build`
