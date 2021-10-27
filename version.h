#ifndef VERSION_H
#define VERSION_H

namespace Version{
	static const long MAJOR  = 0;
	static const long MINOR  = 2;
	static const long BUILD  = 410;

    static std::string getVersion() {
        return
        "v" + std::to_string(Version::MAJOR) +
        "." + std::to_string(Version::MINOR) +
        "." + std::to_string(Version::BUILD);
    }

    int versionNumber() {
        return MAJOR * 1000000 + MINOR * 1000000 + BUILD;
    }
}
#endif //VERSION_H
