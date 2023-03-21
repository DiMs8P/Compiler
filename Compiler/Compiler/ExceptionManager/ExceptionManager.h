#pragma once
#include <string>

class ExceptionManager
{
public:
    void Exception(const std::string& errorMessage);
    void SetOutputFileName(std::string& newFileName);

private:
     std::string _outputFileName = "errors.txt";
};