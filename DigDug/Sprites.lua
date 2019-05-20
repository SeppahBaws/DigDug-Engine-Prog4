spriteRenderConfig = {
	defaultSprite = "Run",
	spriteScale = 3
}

-- Player sprites
player = {
	run = {
		name = "Run",
		fileName = "player-run.png",
		cols = 2,
		rows = 1,
		framerate = 10
	},
	dig = {
		name = "Dig",
		fileName = "player-dig.png",
		cols = 0,
		rows = 1,
		framerate = 10
	},
	pump = {
		name = "Pump",
		fileName = "player-pump.png",
		cols = 2,
		rows = 1,
		framerate = 10
	},
	shoot = {
		name = "Shoot",
		fileName = "player-shoot.png",
		cols = 3,
		rows = 1,
		framerate = 10
	},
	death = {
		name = "Death",
		fileName = "player-death.png",
		cols = 4,
		rows = 1,
		framerate = 10
	}
}

-- Pooka sprites
pooka = {

}

-- Fygar sprites
fygar = {

}



-- Sprites for testing, the idea was to load them from a single file, using a position and offset
-- sprites = {
-- 	run = {
-- 		name = "Run",
-- 		filename = "DigDugSpriteSheet.png",
-- 		xPos = 75,
-- 		yPos = 58,
-- 		frameWidth = 16,
-- 		frameHeight = 16,
-- 		paddingX = 1,
-- 		paddingY = 1,
-- 		cols = 2,
-- 		rows = 1,
-- 		framerate = 10
-- 	},
-- 	dig = {
-- 		name = "Dig",
-- 		filename = "DigDugSpriteSheet.png",
-- 		xPos = 109,
-- 		yPos = 58,
-- 		frameWidth = 16,
-- 		frameHeight = 16,
-- 		paddingX = 1,
-- 		paddingY = 1,
-- 		cols = 2,
-- 		rows = 1,
-- 		framerate = 10
-- 	},
-- 	pump = {
-- 		name = "Pump",
-- 		filename = "DigDugSpriteSheet.png",
-- 		xPos = 143,
-- 		yPos = 58,
-- 		frameWidth = 16,
-- 		frameHeight = 16,
-- 		paddingX = 1,
-- 		paddingY = 1,
-- 		cols = 2,
-- 		rows = 1,
-- 		framerate = 10
-- 	},
-- 	shoot = {
-- 		name = "Shoot",
-- 		filename = "DigDugSpriteSheet.png",
-- 		xPos = 177,
-- 		yPos = 58,
-- 		frameWidth = 16,
-- 		frameHeight = 16,
-- 		paddingX = 1,
-- 		paddingY = 1,
-- 		cols = 3,
-- 		rows = 1,
-- 		framerate = 10
-- 	}
-- }