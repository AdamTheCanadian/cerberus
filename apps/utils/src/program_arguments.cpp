#include "utils/program_arguments.h"
#include <iostream>
#include <getopt.h>

using namespace utils;

utils::ProgramArguments::ProgramArguments(const std::string &programName) :
  program_name_(programName) {

}

void utils::ProgramArguments::ShowUsage() const {
  std::cout << "***** " << program_name_ << " *****" << std::endl;
  for (size_t i = 0; i < args_.size(); i++) {
    std::cout << "\t--";
    std::cout << args_[i];
    if (required_[i]) {
      std::cout << " (required)";
    }
    else {
      std::cout << " (optional)";
    }
    std::cout << ": " << descriptions_[i];
    std::cout << std::endl;
  }
}

void utils::ProgramArguments::AddArgument(const std::string &argName,
                                          const std::string &argDescription,
                                          bool required) {
  // TODO: What happens if argName already exists?
  args_.push_back(argName);
  descriptions_.push_back(argDescription);
  required_.push_back(required);
  // We add an empty place holder string until we parse the arguments
  values_.push_back("");
}

bool utils::ProgramArguments::ParseArguments(int argc, char *argv[]) {
  // Setup the getopt options data structures
  std::vector<option> long_options;

  for (size_t i = 0; i < args_.size(); i++) {
    option opt;
    opt.name = args_[i].c_str();
    if (required_[i]) {
      opt.has_arg = required_argument;
    }
    else {
      opt.has_arg = no_argument;
    }
    opt.flag = nullptr;
    // val is usually used with short/character option identifiers. Since ProgramArguments we only
    // support long options (the -- style), we set val to the argument order (1 indexed hence the +1).
    // This will then be used when parsing to get the parsed option index in args_, values_, etc
    opt.val = (int)i + 1;
    long_options.push_back(opt);
  }
  // getopt requires the last option to be all 0's
  long_options.push_back({nullptr, 0, nullptr, 0});

  int option = 0;
  // This makes getopt_long not exit or display any error messages when encountering an unknown option,
  // we will handle the error message below
  opterr = 0;
  while ((option = getopt_long(argc, argv, "", &long_options[0], nullptr)) != -1) {
    if (option <= args_.size()) {
      values_[option - 1] = std::string(optarg);
    }
    else {
      std::cout << "Unknown option " << argv[optind - 1] << std::endl;
      ShowUsage();
      return false;
    }
  }

  // Check required arguments are present
  bool are_required_present = true;
  for (size_t i = 0; i < required_.size(); i++) {
    if (required_[i]) {
      if (values_[i].size() == 0) {
        are_required_present = false;
        std::cout << "Missing required argument " << args_[i] << std::endl;
      }
    }
  }

  if (!are_required_present) {
    ShowUsage();
  }

  return are_required_present;
}