// $Id: main.cpp,v 1.3 2015-03-25 19:03:01-07 - - $

#include <string>
using namespace std;

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stringset.h"

int main (int argc, char **argv) {
   for (int i = 1; i < argc; ++i) {
      const string* str = intern_stringset (argv[i]);
      printf ("intern (\"%s\") returned %p->\"%s\"\n",
              argv[i], str, str->c_str());
   }
   dump_stringset (stdout);
   return EXIT_SUCCESS;
}

