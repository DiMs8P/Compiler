#include "ExceptionManager.h"
#include <fstream>

ExceptionManager::ExceptionManager(std::ofstream& stream)
{
	_stream = std::move(stream);
}

void ExceptionManager::Exception(const std::string& errorMessage)
{
	if (_stream.is_open())
	{
		_stream << errorMessage << std::endl;
	}
	else
	{
		_stream.open("errors.txt");
		_stream << errorMessage << std::endl;
		_stream.close();
	}

	throw std::exception(errorMessage.c_str());
}
