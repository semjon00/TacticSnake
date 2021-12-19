#ifndef VERSION_H
#define VERSION_H

namespace Version{
    static const long MAJOR  = 0;
    static const long MINOR  = 2;
    static const long BUILD  = 412;
	static const std::string postfix = "";

    static std::string getVersion() {
        return
        "v" + std::to_string(Version::MAJOR) +
        "." + std::to_string(Version::MINOR) +
        "." + std::to_string(Version::BUILD) +
        postfix;
    }

    constexpr static short getVersionColor() {
        if (BUILD == 0) {
            return 12;
        }
        return ((Version::MINOR * 2) + Version::BUILD) % 7 + 1;
    }
}
#endif //VERSION_H
