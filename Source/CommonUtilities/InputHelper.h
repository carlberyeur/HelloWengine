#pragma once

namespace cu
{
	bool ReadFile(const std::string& aFilePath, std::string& aFileContentOut);
	bool ReadFileBinary(const std::string& aFilePath, std::string& aFileContentOut);
}
