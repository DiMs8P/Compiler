#pragma once
#include <string>

class ExceptionManager
{
public:
    static void Exception(const std::string& errorMessage);
    static void SetOutputFileName(std::string& newFileName);

private:
    static std::string _outputFileName = "errors.txt";
};