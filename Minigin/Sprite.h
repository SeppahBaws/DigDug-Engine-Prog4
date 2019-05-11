#pragma once

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	class Texture2D;

	struct SpriteProps
	{
		std::string name = "";
		std::string filename = "";
		int cols = 1;
		int rows = 1;
		float framerate = 0;
	};

	class Sprite final
	{
	public:
		Sprite(const SpriteProps& props);

		void LoadTexture(const std::string& filename);

		void Update();
		void Render(const glm::vec3& pos, int scale);
		void Reset();

		std::string GetName() const { return m_Props.name; }

	private:
		int GetFrameWidth() const;
		int GetFrameHeight() const;

	private:
		std::shared_ptr<Texture2D> m_pSpriteSheet;

		SpriteProps m_Props;
		int m_TextureWidth;
		int m_TextureHeight;

		float m_AccuFrames;
		int m_CurrentFrame;
	};
}
