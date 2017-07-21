#include "stdafx.h"
#include "InputHelper.h"

namespace cu
{
	bool ReadFile(const std::string& aFilePath, std::string& aFileContentOut)
	{
		std::ifstream file(aFilePath);
		if (!file.good())
		{
			return false;
		}

		std::stringstream fileContentStream;
		fileContentStream << file.rdbuf();
		aFileContentOut = fileContentStream.str();

		return !aFileContentOut.empty();
	}

	bool ReadFileBinary(const std::string& aFilePath, std::string& aFileContentOut)
	{
		std::ifstream file(aFilePath, std::ios::binary);
		if (!file.good())
		{
			return false;
		}

		file.seekg(0, file.end);
		std::int64_t sizei = file.tellg();
		if (sizei < 0)
		{
			return false;
		}
		file.seekg(0, file.beg);

		size_t size = static_cast<size_t>(sizei);
		aFileContentOut.resize(size, '\0');

		char* fileContent = const_cast<char*>(aFileContentOut.data());

		if (!file.read(fileContent, sizei).good())
		{
			return false;
		}

		return !aFileContentOut.empty();
	}
}
