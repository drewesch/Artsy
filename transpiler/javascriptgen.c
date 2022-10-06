
// Set of functions to emit MIPS code
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "javascriptgen.h"

FILE * jsCode;

void initJavaScriptFile(){
    // Creates a JavaScript file with generic imports for every file
    jsCode = fopen("artsyCode.js", "a");
}