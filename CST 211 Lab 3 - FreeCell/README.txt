FreeCell - Readme

1. Game is complete, but lacking features I'd like to add. I blame this lack of time on the sorts test. It should meet all
	requirements, but it doesn't have any menus, nor does it have a win screen- just closes on victory.

2. Debug cheats exist, and are as follows:
	Q R - Win game immediately. Currently same as quitting.
	Q F - Force next command to complete. (force select stack, force place stack, cards, etc)

3. Console window buffer size may need to be adjusted. Do this by navigating to the console window's properties page > layout and
	adjust screen buffer dimensions to fit entire game. I use width 120 and height 300, which works flawlessly for me.

4. Do not force place cards if the dimensions of the stack would go out of bounds of the height of the board. It will throw an
	exception, which is not caught as it's impossible to do this without debugging cheats anyway.

5. Enjoy!