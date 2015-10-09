// $Id: stringset.h,v 1.3 2015-03-25 19:03:01-07 - - $

#ifndef __STRINGSET__
#define __STRINGSET__

#include <string>

#include <stdio.h>

const std::string* intern_stringset (const char*);

void dump_stringset (FILE*);

#endif

