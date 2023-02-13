#include "Resources.h"

#ifdef TARGET_OS_MAC
#include "ResourcePath.h"
#else
#include <windows.h>
#include <iostream>
#endif

std::string Resources::getAssetPath()
{
	 std::string project_assets_path { "assets/" };
#ifdef TARGET_OS_MAC
	return resourcePath() + project_assets_path;
#else
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	return std::string(buf) + '\\';
#endif
}
