#include "ErrorHandling.h"
#include <sstream>

ErrorHandling::ErrorHandling(int line, const char* file) noexcept : line(line), file(file)
{}

const char* ErrorHandling::what() const noexcept
{
	std::ostringstream stream;
	stream << GetType() << std::endl << GetOriginString();
	whatBuffer = stream.str();
	return whatBuffer.c_str();
}

const char* ErrorHandling::GetType() const noexcept
{
	return "Error";
}

int ErrorHandling::GetLine() const noexcept
{
	return line;
}

const std::string& ErrorHandling::GetFile() const noexcept
{
	return file;
}

std::string ErrorHandling::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}
