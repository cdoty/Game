#include "Player.h"
#include "PlayerDefines.h"
#include "../System/InputDefines.h"
#include "../SystemLib/Include/Input.h"
#include "../SystemLib/Include/Sprites.h"

byte	playerX;		// Player X position
byte	currentFrame;	// Current frame
byte	frameDelay;		// Frame delay

void setupPlayer()
{
	playerX			= PlayerStartX;
	currentFrame	= 0;
	frameDelay		= AnimationDelay;

	selectSprite(PlayerSprite);
	setSpritePosition(playerX, PlayerStartY - ClawYOffset);
	setSpriteTileAndColor(PlayerSpritePattern + 9 + currentFrame, PlayerSpriteColor);

	selectSprite(PlayerSprite + 1);
	setSpritePosition(playerX + 8, PlayerStartY - ClawYOffset);
	setSpriteTileAndColor(PlayerSpritePattern + 10 + currentFrame, PlayerSpriteColor);

	selectSprite(PlayerSprite + 2);
	setSpritePosition(playerX, PlayerStartY);
	setSpriteTileAndColor(PlayerSpritePattern + currentFrame, PlayerSpriteColor);

	selectSprite(PlayerSprite + 3);
	setSpritePosition(playerX + 8, PlayerStartY);
	setSpriteTileAndColor(PlayerSpritePattern + 1 + currentFrame, PlayerSpriteColor);
}

void updatePlayer()
{
	byte	joy1	= readJoystick1();

	if ((joy1 & JoypadRight) != 0)
	{
		byte	allowedMove	= MaxPlayerRight - playerX;

		if (MoveSpeed >= allowedMove)
		{
			playerX	= MaxPlayerRight;

			resetAnimationFrame();
		}

		else
		{
			playerX	+= MoveSpeed;
			
			increaseAnimationFrame();
		}

		updatePlayerPosition();
	}

	else if ((joy1 & JoypadLeft) != 0)
	{
		if (playerX < MinPlayerLeft + MoveSpeed)
		{
			playerX	= MinPlayerLeft;

			resetAnimationFrame();
		}

		else
		{
			playerX	-= MoveSpeed;
			
			decreaseAnimationFrame();
		}

		updatePlayerPosition();
	}

	else
	{
		resetAnimationFrame();
	}
}

void updatePlayerPosition()
{
	selectSprite(PlayerSprite);
	setSpritePosition(playerX, PlayerStartY - ClawYOffset);

	selectSprite(PlayerSprite + 1);
	setSpritePosition(playerX + 8, PlayerStartY - ClawYOffset);

	selectSprite(PlayerSprite + 2);
	setSpritePosition(playerX, PlayerStartY);

	selectSprite(PlayerSprite + 3);
	setSpritePosition(playerX + 8, PlayerStartY);

	updateSprites();
}

void updatePlayerTile()
{
	// Each sprite is two tiles
	byte frame	= currentFrame + currentFrame;

	selectSprite(PlayerSprite + 2);
	setSpriteTile(PlayerSpritePattern + frame);

	selectSprite(PlayerSprite + 3);
	setSpriteTile(PlayerSpritePattern + 1 + frame);

	updateSprites();
}

void increaseAnimationFrame()
{
	frameDelay--;

	if (0 == frameDelay)
	{
		currentFrame++;

		if (AnimationFrames == currentFrame)
		{
			currentFrame	= 0;
		}

		frameDelay	= AnimationDelay;

		updatePlayerTile();
	}
}

void decreaseAnimationFrame()
{
	frameDelay--;

	if (0 == frameDelay)
	{
		if (currentFrame > 0)
		{
			currentFrame--;
		}

		else
		{
			currentFrame	= AnimationFrames - 1;
		}

		frameDelay	= AnimationDelay;

		updatePlayerTile();
	}
}

void resetAnimationFrame()
{
	currentFrame	= 0;
	frameDelay		= AnimationDelay;

	updatePlayerTile();
}
