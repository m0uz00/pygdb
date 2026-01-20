#include <stdlib.h>
#include <Python.h>

#include "../include/utils.h"

void run_file(program* program){

  Py_Initialize();

  PyRun_InteractiveLoop(stdin, "<stdin>");

  Py_Finalize();  
}
