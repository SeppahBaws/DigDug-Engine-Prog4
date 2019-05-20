#pragma once
#include "Singleton.h"

extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

namespace dae
{
	class Sprite;
	struct SpriteRenderConfig;

	class LuaHelpers final : public Singleton<LuaHelpers>
	{
	public:
		LuaHelpers();

		// Public functions
		void OpenFile(const std::string& filename);

		// Sprites
		SpriteRenderConfig ReadSpriteConfig(const std::string& varName);
		std::vector<Sprite> ReadSprites(const std::string& arrayName, const std::vector<std::string>& spriteKeys);

		// Static functions for easy access
		static void Init();
		static void Cleanup();

	private:
		// Internal functions
		void Init_internal();
		void Cleanup_internal();

	private:
		lua_State* L;
	};
}
