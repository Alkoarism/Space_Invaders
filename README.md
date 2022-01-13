# Space_Invaders
This is a clone project of the game Space Invaders for learning purposes.
With this I intend to use all the knowledge acquired after reading the "Learn OpenGL" book and practice and further improve my skills with OOP, while also learning more about the C++ language and Graphics Programming.

Currently there is only a prototype of the main game loop:

![image](https://user-images.githubusercontent.com/69710741/149419224-9363547c-dc7d-4ac8-8424-8dc2da9a70c2.png)

If you want to download the .exe file, you can find on "/builds/0_1_3- initial_game_loop", simply download the entire folder and run the .exe file inside of it. It should run as demonstrated on the GIF.
It is also possible to manipulate the number and position of the aliens on the level changing the contents of the "classic.lvl" file (/res/levels) (Although this feature have not been tested or debugged in this release):
- Numbers must be separated by a space and represent the type of enemy:
	- 0: Empty;
	- 1: Circle alien;
	- 2: Square alien;
	- 3: Triangle alien;

- Any other number has no meaning to the game.

The used keys are:
- A/D or LEFT/RiGHT: Move player pad;
- SPACE: Shoot;
- ESC: Close application.

External sources:
Text rendering was made using CBFG, and his example code, although with some changes.
https://github.com/CodeheadUK/CBFG

Learn OpenGL book site:
https://learnopengl.com/

The Cherno´s youtube channel, OpenGL series:
https://www.youtube.com/channel/UCQ-W1KE9EYfdxhL6S4twUNw
