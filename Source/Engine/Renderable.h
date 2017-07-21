#pragma once

namespace wendy
{
	class CScene;
	enum eRenderPipeline : std::uint16_t;
	
	class CRenderable
	{
	public:
		CRenderable();
		CRenderable(const CRenderable& aCopy) = default;
		~CRenderable();

		explicit operator cu::Matrix44f&() const;
		bool IsValid() const;

	private:
		CScene* myScene;
		eRenderPipeline myPipeline;
		std::uint16_t myRenderableID;
	};
}
