#include "main_args.h"
#include "dbug.h"
#include "str.h"
#include "globals.h"
#include "usage.h"
#include "ctinfo.h"
#include "phase_options.h"
#include <stdlib.h> // um strtol zu verwenden



// kommanozeilen commandos 
void OPTcheckOptions( int argc, char **argv)
{
  DBUG_ENTER("OPTcheckOptions");

  ARGS_BEGIN( argc, argv);

  ARGS_OPTION( "b", PHOinterpretBreakOption( ARG)) //break Option

  ARGS_FLAG( "h", USGprintUsage(); exit(0););

  ARGS_OPTION( "o", global.outfile = STRcpy( ARG));

  ARGS_OPTION( "v", ARG_RANGE(global.verbosity, 0, 3));

  ARGS_FLAG( "tc", global.treecheck = TRUE); 

  ARGS_OPTION( "#", DBUG_PUSH( STRcpy( ARG)));

  //Super Strength Reduction-Option
  ARGS_OPTION("ssr", {
    printf("DEBUG: ARG received: '%s'\n", ARG);
    char *endptr;
    SSR_maxFactor = strtol(ARG, &endptr, 10);  // konvertiert arg zu Ganzzahl
    if (*endptr != '\0' || SSR_maxFactor <= 0) {
        fprintf(stderr, "Error: ssr must be a positive integer.\n");
        exit(1);
    }
    if (SSR_maxFactor > 50) {
          fprintf(stderr, "Warning: ssr exceeds the recommended limit (50). Using 50 instead.\n");
          SSR_maxFactor = 50;
}

    });

  ARGS_ARGUMENT( global.infile = STRcpy( ARG); );
  
  ARGS_UNKNOWN( ARGS_ERROR( "Invalid command line entry"));

  ARGS_END();

  if (global.infile == NULL) {
    CTIabort( "No input file given.");
  }

  DBUG_VOID_RETURN;
}
