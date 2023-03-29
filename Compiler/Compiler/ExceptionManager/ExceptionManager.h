#pragma once
#include <fstream>
#include <string>

class ExceptionManager
{
public:
	ExceptionManager(std::ofstream& stream);
	void Exception(const std::string& errorMessage);

private:
	std::ofstream _stream;
};