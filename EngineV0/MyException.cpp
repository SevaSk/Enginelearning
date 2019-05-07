#include "MyException.h"
#include <sstream>

MyException::MyException(int line, const char* file) noexcept :
	line(line), 
	file(file)
{}

const char* MyException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl << GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* MyException::GetType() const noexcept
{
	return "My Exception";
}

int MyException::getLine() const noexcept 
{
	return line;
}

const std::string& MyException::GetFile() const noexcept
{
	return file;
}

std::string MyException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}