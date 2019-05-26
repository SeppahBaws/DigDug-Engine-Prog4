#include "pch.h"
// ReSharper Disable Once CppUnusedIncludeDirective
#include <vld.h>
#include "DigDugGame.h"

int main()
{
	dae::WindowProperties properties
	{
		672, 816,
		"DigDug - Seppe Dekeyser - 2DAE06 - 2018-2019"
	};

	DigDugGame game;
	game.Initialize(properties);
	game.Run();

	return 0;
}
