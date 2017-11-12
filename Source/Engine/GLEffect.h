#pragma once

namespace pulp
{
	class CGLUniformBuffer;

	class CGLEffect
	{
	public:
		CGLEffect();
		CGLEffect(CGLEffect&& aTemporary);
		~CGLEffect();

		CGLEffect& operator=(CGLEffect&& aTemporary);

		bool Init(const std::string& aVertexPath, const std::string& aPixelPath, const cu::CVector<std::string>& aInputAttributes, const cu::CVector<std::string>& aConstantBuffers);
		void Activate();

		CGLUniformBuffer GetUniformBuffer(const std::string& aUniformName) const;
		CGLUniformBuffer GetUniformBuffer(const size_t aHashedUniformName) const;

		void Destroy();

		CGLEffect(const CGLEffect& aCopy) = delete;
		CGLEffect& operator=(const CGLEffect& aCopy) = delete;

	private:
		static bool CompileShader(const std::string& aFileContent, const unsigned int aShaderStage, unsigned int& aShaderIDOut);
		static bool LinkShader(const unsigned int aShaderProgram);

		std::array<size_t, 8> myConstantBufferNames;
		std::array<int, 8> myConstantBufferLocations;

		std::uint32_t myVertexShader;
		std::uint32_t myFragmentShader;
		std::uint32_t myShaderProgram;
	};
}
