#include "ExceptionManager.h"
#include <fstream>

void ExceptionManager::Exception(const std::string& errorMessage)
{
    std::ofstream errorStream;
    errorStream.open (_outputFileName);
    errorStream << errorMessage;
    errorStream.close();
}

void ExceptionManager::SetOutputFileName(std::string& newFileName)
{
    _outputFileName.swap(newFileName);
}