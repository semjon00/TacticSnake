#ifndef VERSION_H
#define VERSION_H

namespace Version{
	static const long MAJOR  = 0;
	static const long MINOR  = 2;
	static const long BUILD  = 402;

	static const std::string versionString = "v" + std::to_string(Version::MAJOR) + "." + std::to_string(Version::MINOR) +
                           "." + std::to_string(Version::BUILD);
}
#endif //VERSION_H
