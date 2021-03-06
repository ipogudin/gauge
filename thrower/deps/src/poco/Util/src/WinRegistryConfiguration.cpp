//
// WinRegistryConfiguration.cpp
//
// $Id: //poco/1.4/Util/src/WinRegistryConfiguration.cpp#4 $
//
// Library: Util
// Package: Windows
// Module:  WinRegistryConfiguration
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#if !defined(_WIN32_WCE)


#include "Poco/Util/WinRegistryConfiguration.h"
#include "Poco/Util/WinRegistryKey.h"
#include "Poco/NumberFormatter.h"
#include "Poco/NumberParser.h"
#include "Poco/Exception.h"


namespace Poco {
namespace Util {


WinRegistryConfiguration::WinRegistryConfiguration(const std::string& rootPath, REGSAM extraSam): _rootPath(rootPath), _extraSam(extraSam)
{
	// rootPath must end with backslash
	if (!_rootPath.empty())
	{
		if (_rootPath[_rootPath.length() - 1] != '\\')
			_rootPath += '\\';
	}
}


WinRegistryConfiguration::~WinRegistryConfiguration()
{
}


bool WinRegistryConfiguration::getRaw(const std::string& key, std::string& value) const
{
	std::string keyName;
	std::string fullPath = _rootPath + convertToRegFormat(key, keyName);
	WinRegistryKey aKey(fullPath, true, _extraSam);
	bool exists = aKey.exists(keyName);
	if (exists)
	{
		WinRegistryKey::Type type = aKey.type(keyName);

		switch (type)
		{
		case WinRegistryKey::REGT_STRING:
			value = aKey.getString(keyName);
			break;
		case WinRegistryKey::REGT_STRING_EXPAND:
			value = aKey.getStringExpand(keyName);
			break;
		case WinRegistryKey::REGT_DWORD:
			value = Poco::NumberFormatter::format(aKey.getInt(keyName));
			break;
		default:
			exists = false;
		}
	}
	return exists;
}


void WinRegistryConfiguration::setRaw(const std::string& key, const std::string& value)
{
	std::string keyName;
	std::string fullPath = _rootPath + convertToRegFormat(key, keyName);
	WinRegistryKey aKey(fullPath, false, _extraSam);
	aKey.setString(keyName, value);
}


void WinRegistryConfiguration::enumerate(const std::string& key, Keys& range) const
{
	std::string keyName;
	std::string fullPath = _rootPath + convertToRegFormat(key, keyName);

	if (fullPath.empty())
	{
		// return all root level keys
		range.push_back("HKEY_CLASSES_ROOT");
		range.push_back("HKEY_CURRENT_CONFIG");
		range.push_back("HKEY_CURRENT_USER");
		range.push_back("HKEY_LOCAL_MACHINE");
		range.push_back("HKEY_PERFORMANCE_DATA");
		range.push_back("HKEY_USERS");
	}
	else
	{
		fullPath += '\\';
		fullPath += keyName;
		WinRegistryKey aKey(fullPath, true, _extraSam);
		aKey.values(range);
		aKey.subKeys(range);
	}
}


void WinRegistryConfiguration::removeRaw(const std::string& key)
{
	throw Poco::NotImplementedException("Removing a key in a WinRegistryConfiguration");
}


std::string WinRegistryConfiguration::convertToRegFormat(const std::string& key, std::string& value) const
{
	std::size_t pos = key.rfind('.');
	if (pos == std::string::npos)
	{
		value = key;
		return std::string();
	}
	std::string prefix(key.substr(0,pos));
	value = key.substr(pos + 1);
	Poco::translateInPlace(prefix, ".", "\\");
	return prefix;
}


} } // namespace Poco::Util


#endif // !defined(_WIN32_WCE)
