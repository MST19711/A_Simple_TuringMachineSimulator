#include "TM.h"
#include <fstream>
#include <string>

#ifndef TM_READER
#define TM_READER
bool read_TM(std::string path, TuringMachine &turningMachine);
#endif