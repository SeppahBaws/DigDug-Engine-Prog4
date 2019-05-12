#include "MiniginPCH.h"
#include "LuaHelpers.h"
#include <LuaBridge/LuaBridge.h>

#include "Sprite.h"
#include "SpriteRenderComponent.h"

// type-alias the luabridge namespace
namespace lb = luabridge;

namespace dae
{
	LuaHelpers::LuaHelpers()
		: L(nullptr)
	{
	}

	void LuaHelpers::OpenFile(const std::string& filename)
	{
		luaL_dofile(L, filename.c_str());
		luaL_openlibs(L);
		lua_pcall(L, 0, 0, 0);
	}

	SpriteRenderConfig LuaHelpers::ReadSpriteConfig(const std::string& varName)
	{
		lb::LuaRef lb_config = lb::getGlobal(L, varName.c_str());
		
		SpriteRenderConfig config{};
		config.defaultSprite = lb_config["defaultSprite"].cast<std::string>();
		config.scale = lb_config["spriteScale"].cast<int>();

		return config;
	}

	std::vector<Sprite> LuaHelpers::ReadSprites(const std::string& arrayName, const std::vector<std::string>& spriteKeys)
	{
		std::vector<Sprite> sprites{};

		lb::LuaRef lb_sprites = lb::getGlobal(L, arrayName.c_str());

		for (const std::string& key : spriteKeys)
		{
			SpriteProps props{};

			// Read the current sprite object
			lb::LuaRef lb_sprite = lb_sprites[key.c_str()];

			// Fill the SpriteProps struct
			props.name = lb_sprite["name"].cast<std::string>();
			props.filename = lb_sprite["fileName"].cast<std::string>();
			props.cols = lb_sprite["cols"].cast<int>();
			props.rows = lb_sprite["rows"].cast<int>();
			props.framerate = lb_sprite["framerate"].cast<float>();

			Sprite sprite{ props };
			sprites.push_back(sprite);
		}

		return sprites;
	}

	void LuaHelpers::Init()
	{
		GetInstance().Init_internal();
	}

	void LuaHelpers::Cleanup()
	{
		GetInstance().Cleanup_internal();
	}

	void LuaHelpers::Init_internal()
	{
		L = luaL_newstate();
	}

	void LuaHelpers::Cleanup_internal()
	{
		lua_close(L);
	}
}
