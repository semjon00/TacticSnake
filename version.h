#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 0;
	static const long MINOR  = 2;
	static const long BUILD  = 305;
	static const long REVISION  = 1180;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 482;
	#define RC_FILEVERSION 0,2,305,1180
	#define RC_FILEVERSION_STRING "0, 2, 305, 1180\0"
	static const char FULLVERSION_STRING [] = "0.2.305.1180";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 7;
	

}
#endif //VERSION_H
