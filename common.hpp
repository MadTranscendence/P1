#ifndef COMMON_HPP
#define COMMON_HPP


#include <iostream>
/*
All implementation files must #include "config.h" first. Header files should never include "config.h".
All implementation files must #include the primary header second, just after "config.h".
Other #include statements should be in sorted order (case sensitive, as done by the command-line sort tool or the Xcode sort selection command).
Don't bother to organize them in a logical order.
Includes of system headers must come after includes of other headers.

This is a header included by every single file.
It should include definitions of most basic types and utilities
(like asserts and simple templates. It usually means most common
header files for C standard library like  etc. and
on Windows.\
Resist temptation to include too much in this file - it’ll lead
to insanity.


Static data members should be prefixed by "s_". Other data members should be prefixed by "m_".
*/

void SDLLog(int result);

#endif
