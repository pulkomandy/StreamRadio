/*
 * Copyright (C) 2017 Kai Niessen <kai.niessen@online.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef _HTTP_UTILS_H
#define _HTTP_UTILS_H


#include <DataIO.h>
#include <HttpRequest.h>
#include <Socket.h>
#include <StringList.h>
#include <Url.h>


// Wrapper class to ensure compatibility with old and new versions of the BUrl API
// Make sure to properly encode URLs as needed.
class MyUrl: public BUrl
{
	public:
	MyUrl()
		: BUrl()
	{
	}

	MyUrl(const BUrl& base, const BString& relative)
		: BUrl(base, relative)
	{
	}

#if B_HAIKU_VERSION < B_HAIKU_VERSION_1_BETA_6
	MyUrl(const BUrl& other)
		: BUrl(other)
	{
	}

	MyUrl(const char* string)
		: BUr(string)
	{
		UrlEncode();
	}

	void SetUrlString(const char* string)
	{
		BUrl::SetUrlString(string);
		UrlEncode();
	}
#else
	MyUrl(const BUrl& other)
		: BUrl(other)
	{
	}

	MyUrl(const char* string)
		: BUrl(string, true)
	{
	}

	void SetUrlString(const char* string)
	{
		BUrl::SetUrlString(string, true);
	}
#endif
};



using namespace BPrivate::Network;


class HttpUtils {
public:
	static status_t CheckPort(BUrl url, MyUrl* newUrl, uint32 flags = 0);

	static BMallocIO* GetAll(BUrl url, BHttpHeaders* returnHeaders = NULL, bigtime_t timeOut = 3000,
		BString* contentType = NULL, size_t sizeLimit = 0);
};


#endif	// _HTTP_UTILS_H
