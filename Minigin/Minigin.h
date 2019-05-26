#pragma once

struct SDL_Window;

namespace dae
{
	struct WindowProperties
	{
		int width;
		int height;
		std::string title;
	};

	class Minigin
	{
		const int m_MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_pWindow{};
	public:
		void Initialize(const WindowProperties& properties);
		virtual void LoadGame() const = 0;
		void Cleanup();
		void Run();
	};
}