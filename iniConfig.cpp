﻿#include "dinput8.h"
#include "iniConfig.h"
#include <algorithm>
#include <string>

iniConfig::iniConfig(LPCTSTR fileName)
{
	this->fileName = fileName;

	SetLastError(ERROR_SUCCESS);
	GetPrivateProfileSectionNames(buffer, 512, fileName);
	if (GetLastError() == ERROR_FILE_NOT_FOUND)
		logFile << "Config: file not found!" << std::endl;
}

bool iniConfig::get(LPCTSTR section, LPCTSTR key)
{
	SetLastError(ERROR_SUCCESS);
	DWORD result = GetPrivateProfileString(section, key, nullptr, buffer, 512, fileName);
	return GetLastError() != ERROR_FILE_NOT_FOUND && result > 0;
}

template <typename T>
T printError(LPCTSTR section, LPCTSTR key, T defValue)
{
	logFile << "Config: " << section << "->" << key << " has invalid value, using default (" << defValue << ")" << std::endl;
	return defValue;
}

iniConfig::stringType iniConfig::getStr(LPCTSTR section, LPCTSTR key, stringType defValue)
{
	if (!get(section, key))
		printError(section, key, defValue);
	return buffer;
}

int iniConfig::getInt(LPCTSTR section, LPCTSTR key, int defValue)
{
	try
	{
		if (get(section, key))
			return std::stoi(buffer, nullptr, 0);
	}
	catch (...) {}
	return printError(section, key, defValue);
}

unsigned iniConfig::getUInt(LPCTSTR section, LPCTSTR key, unsigned defValue)
{
	try
	{
		if (get(section, key))
			return std::stoul(buffer, nullptr, 0);
	}
	catch (...) {}
	return printError(section, key, defValue);
}

float iniConfig::getFloat(LPCTSTR section, LPCTSTR key, float defValue)
{
	try
	{
		if (get(section, key))
			return std::stof(buffer, nullptr);
	}
	catch (...) {}
	return printError(section, key, defValue);
}

double iniConfig::getDouble(LPCTSTR section, LPCTSTR key, double defValue)
{
	try
	{
		if (get(section, key))
			return std::stod(buffer, nullptr);
	}
	catch (...) {}
	return printError(section, key, defValue);
}

bool iniConfig::getBool(LPCTSTR section, LPCTSTR key, bool defValue)
{
	try
	{
		if (get(section, key))
		{
			std::wstring str(buffer);
			transform(str.begin(), str.end(), str.begin(), tolower);
			if (str == L"true" || str == L"yes" || str == L"on")
				return true;
			if (str == L"false" || str == L"no" || str == L"off")
				return false;
			throw std::invalid_argument("invalid value");
		}
	}
	catch (...) {}
	return printError(section, key, defValue);
}