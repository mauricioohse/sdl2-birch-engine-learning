# Introduction
This is a 2D game engine heavily based on Carl Birch Engines [carlbirch/BirchEngine: Start (github.com)](https://github.com/carlbirch/BirchEngine)

I made this following his youtube video series that can be found here: [https://goo.gl/VERhC5](https://goo.gl/VERhC5)

The big idea is that this is a pure C++ + SDL2 game engine that can be used for 2D games. It is implementented using ECS architecture, so it is fairly flexible. The main capabilities are:
* ECS implementation 
* loading tilemap and collision mapping from txt files
* 
# Getting started

At the moment, to compile and run, you need to setup the libraries SDL2, SDL2_image and SDL2_ttf.  They need to be linked properly, see Carl's videos #1, #4 and #23 for that. In the future I would like to make the whole repo not be dependant on that.

Also, I ran using Microsoft Visual Studio 2022.


# Todo:
- [ ] make all the dependancies be on the repo (easier clone + compile)
- [ ] add SceneManager
- [ ] add audio support
- [ ] add mouse inputs
- [ ] add mouse interaction with UI
- [ ] add save states

