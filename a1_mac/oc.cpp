#include <iostream>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <unistd.h>
#include <string.h>
#include <fstream>
using namespace std;

#include "stringset.h"
//#include "auxlib.h"


const string CPP = "/usr/bin/cpp";
const size_t LINESIZE = 1024;

// Chomp the last character from a buffer if it is delim.
void chomp (char* string, char delim) {
   size_t len = strlen (string);
   if (len == 0) return;
   char* nlpos = string + len - 1;
   if (*nlpos == delim) *nlpos = '\0';
}

void cppparse (FILE* pipe, char* filename){
   int linenr = 1;
   char inputname[LINESIZE];
   strcpy (inputname, filename);
   for (;;) {
      char buffer[LINESIZE];
      char* fgets_rc = fgets (buffer, LINESIZE, pipe);
      if (fgets_rc == NULL) break;
      chomp (buffer, '\n');
      /*printf ("%s:line %d: [%s]\n", filename, linenr, buffer);
       http://gcc.gnu.org/onlinedocs/cpp/Preprocessor-Output.html
      int sscanf_rc = sscanf (buffer, "# %d \"%[^\"]\"",
                              &linenr, filename);
      if (sscanf_rc == 2) {
         printf ("DIRECTIVE: line %d file \"%s\"\n", linenr, filename);
         continue;
      }*/
      char* savepos = NULL;
      char* bufptr = buffer;
      for (int tokenct = 1;; ++tokenct) {
         char* token = strtok_r (bufptr, " \t\n", &savepos);
         bufptr = NULL;
         if (token == NULL) break;
         //printf ("token %d.%d: [%s]\n")
           //      linenr, tokenct, token);
         if (token[0] != '#') intern_stringset (token);
      }
      ++linenr;
   }
}

int main (int argc, char** argv) {
	int c;
	string dvalue;;
	while ((c = getopt (argc, argv, "ly@:D:")) != -1){
    switch (c)
      {
      case 'l':
        break;
      case 'y':
        break;
      case '@':
	break;
      case 'D':
        dvalue = optarg;
        break;
      case '?':
        if (optopt == 'c')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }
   }

   // get the filename and check to see if it has an .oc suffix
   int i = 1;
   string input = argv[i];
   while (i < argc){
      input = argv[i];
      size_t inputSearch = input.find (".oc");
      if (input[0] != '-' && inputSearch != std::string::npos){
         break;
         //cout << input << endl;
         //i++;
      }else if (input[0] != '-' && inputSearch == std::string::npos){
         //print system errors and exit
         fprintf (stderr, "The program's suffix must be \".oc\"\n");
      	exit(1);
         
      }else{
         i++;
      }
   }

   // create the .str file
   const char* c_input = input.c_str ();
   char* filee = strdup (c_input);
   char* str_file = basename (filee);
   string prog = str_file;
   size_t dotchop = prog.find_last_of ('.', prog.length());
   string finalfile = prog.substr (0, dotchop);
   finalfile = finalfile + ".str";
   const char* fin = finalfile.c_str ();

   FILE* out = fopen (fin, "w");
	if (out == NULL){
		fprintf (stderr, "out.str failed to close");
   	exit (1);
	}
	
   string command = CPP + " " + str_file;      
   //printf ("command=\"%s\"\n", command.c_str());
   FILE* pipe = popen (command.c_str(), "r");
   if (pipe == NULL) {
   	fprintf (stderr, "CPP pipe didn't open\n");
   	exit (1);
      //syserrprintf (command.c_str());
   }else {      
   	cppparse (pipe, str_file);
   	int pclose_rc = pclose (pipe);
   	if (pclose_rc != 0){
   	   fprintf (stderr, "CPP pipe failed to close\n");
   		exit (1);	
   	}
      //eprint_status (command.c_str(), pclose_rc);
   }
   dump_stringset (out);
   int fcloser = fclose (out);
   if (fcloser != 0){
   	fprintf (stderr, "out.str failed to close\n");
   	exit (1);
   }
   //return get_exitstatus();
   return 0;
}


