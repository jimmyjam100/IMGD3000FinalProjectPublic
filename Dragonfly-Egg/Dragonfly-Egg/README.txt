This was made on Windows using Microsoft Visual Studio 2019.
There are source and header files.
The Source files are: Animation.cpp Box.cpp Clock.cpp, Color.cpp, DisplayManager.cpp, Event.cpp, EventCollision.cpp, EventKeyboard.cpp, EventMouse.cpp, EventOut.cpp, EventStep.cpp, EventView.cpp Frame.cpp game.cpp, GameManager.cpp, InputManager.cpp, Manager.cpp, Music.cpp Object.cpp, ResourceManager.cpp, Sound.cpp Sprite.cpp SpriteResourceManager.cpp Star.cpp, TestObject.cpp, TestObject2.h, Vector.cpp, WorldManager.cpp.

Header Files are: Animation.h Clock.h, Color.h, DisplayManager.h, Event.h, EventCollision.h EventKeyboard.h, EventMouse.h, EventOut.h, EventStep.h,  EventView.h Frame.h GameManager.h, LobManager.h, InputManager.h, Manager.h, Music.h Object.h, ResourceManager.h Sound.h Sprite.h SpriteResourceManager.h Star.h, TestObject.h, TestObject2.h, Vector.h, WorldManager.h.

The files Star.h, Star.cpp, TestObject.cpp, TestObject.h, TestObject2.cpp, TestObject2.h, and game.cpp are not needed for the game engine and only used for demenstation and testing purposes.

The Files are all located in the repo.

To compile you will need visual studio 2019. You can then open up the project by double clicking on the "Dragonfly-Egg.sln" file. Then to run it you can press F5 or click local windows debugger.

The program will run a little test where you control a saucer with the arrow keys. If you ever do anything with the mouse the f will move diagonally. There are stars that will move from left to right, and if you touch them they will disapear, There is also an saucer that acts as a wall to both you and the stars. Also if you move off the screen you will be moved to a set position on the map. I feel like this shows off all of the functionallity that was added in this project step. Also if you hit a star an explosion sound will play

FOR GRADER: I had trouble concatenatng some of the variables into log statements, so half of the test output is done on the console and half of it is done in the draggonfly.log file. Sorry for the inconvience.