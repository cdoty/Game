#include "Game.h"
#include "GraphicsData.h"
#include "Player.h"
#include "RAMDefines.h"
#include "../System/VRAMDefines.h"
#include "../SystemLib/Include/Decompression.h"
#include "../SystemLib/Include/ExtraRam.h"
#include "../SystemLib/Include/Graphics.h"
#include "../SystemLib/Include/Input.h"
#include "../SystemLib/Include/Sprites.h"
#include "../SystemLib/Include/System.h"

bool	exitGame;

void startGame()
{
	exitGame	= false;

	clearJoysticks();
	clearSprites();

	setupGameSprites();

	// Decompress the top screen patterns, color map, and tile map
	decompressToVRAM(Background1Pat, Tile1VRAM, Background1PatLength);
	decompressToVRAM(Background1Col, Color1VRAM, Background1ColLength);
	decompressToVRAM(Background1Scn, Screen1VRAM, Background1ScnLength);

	// Decompress the middle screen patterns, color map, and tile map
	decompressToVRAM(Background2Pat, Tile2VRAM, Background2PatLength);
	decompressToVRAM(Background2Col, Color2VRAM, Background2ColLength);
	decompressToVRAM(Background2Scn, Screen2VRAM, Background2ScnLength);

	// Decompress the bottom screen patterns, color map, and tile map
	decompressToVRAM(Background3Pat, Tile3VRAM, Background3PatLength);
	decompressToVRAM(Background3Col, Color3VRAM, Background3ColLength);
	decompressToVRAM(Background3Scn, Screen3VRAM, Background3ScnLength);
	
	// Decompress the sprite patterns
	decompressToVRAM(Sprites, SpritePattern, SpritesLength);
	
	turnOnScreen();
	enableIRQ();
		
	while (!exitGame)
	{
		waitForVBlank();
		updateJoysticks();

		updateGame();
	}

	disableIRQ();
	turnOffScreen();
}

void updateGame()
{
	updatePlayer();
}

void setupGameSprites()
{
	setupRamIcon();
	setupPlayer();
	updateSprites();
}

void setupRamIcon()
{
	if (1 == expandedRAMAvailable())
	{
		selectSprite(RAMSprite);
		setSpritePosition(RAMStartX, RAMStartY);
		setSpriteTileAndColor(RAMSpritePattern, RAMSpriteColor);

		selectSprite(RAMSprite + 1);
		setSpritePosition(RAMStartX + 8, RAMStartY);
		setSpriteTileAndColor(RAMSpritePattern + 1, RAMSpriteColor);
	}
}
