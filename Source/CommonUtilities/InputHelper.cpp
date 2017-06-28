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
}
