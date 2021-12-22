# Space_Invaders
This is a clone project of the game Space Invaders for learning purposes.
With this I intend to use all the knowledge acquired after reading the "Learn OpenGL" book and practice and further improve my skills with OOP, while also learning more about the C++ language and Graphics Programming.

Currently there is only a prototype of the main game screen:

![SpaceInvaders_MenuGIF](https://user-images.githubusercontent.com/69710741/130007608-205f6ac5-25f5-4507-a4c7-789d460ea34a.gif)

If you want to download the .exe file, you can find on "/builds/0_1_1- prototype_demo", simply download the entire folder and run the .exe file inside of it. It should run as demonstrated on the GIF.
It is also possible to manipulate the number and position of the aliens on the level changing the contents of the "test.lvl" file (/res/levele):
- Numbers must be separated by a space and represent the type of enemy:
	- 0: Empty;
	- 1: Circle alien;
	- 2: Square alien;
	- 3: Triangle alien;
	- 4: UFO;

- Any other number has no meaning to the game.

The used keys are:
- A/D: Move player pad;
- ESC: Close application.

External sources:
Text rendering was made using CBFG, and his example code, although with some changes.
https://github.com/CodeheadUK/CBFG

Learn OpenGL book site:
https://learnopengl.com/

The Cherno´s youtube channel, OpenGL series:
https://www.youtube.com/channel/UCQ-W1KE9EYfdxhL6S4twUNw