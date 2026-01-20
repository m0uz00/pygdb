#include <stdlib.h>
#include <Python.h>

#include "../include/utils.h"

void run_file(program* program){

  PyStatus status;
  PyConfig config;
  PyConfig_InitPythonConfig(&config);

  status = Py_InitializeFromConfig(&config);
  if (PyStatus_Exception(status)) {
    goto exception;
  }
  PyConfig_Clear(&config);
  if (Py_FinalizeEx() < 0) {
    exit(120);
  }

  exception:
     PyConfig_Clear(&config);
     Py_ExitStatusException(status);
}
