#include <iostream>
#include "utils/program_arguments.h"

int main(int argc, char *argv[]) {

  utils::ProgramArguments program_arguments("Kitti Stereo");
  program_arguments.AddArgument("dir", "full path to directory example: /some/path/to/kitti", true);

  program_arguments.ParseArguments(argc, argv);
//  program_arguments.ShowUsage();
  return 1;
}