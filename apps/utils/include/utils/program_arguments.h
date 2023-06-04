#ifndef CERBERUS_APPS_UTILS_INCLUDE_UTILS_PROGRAM_ARGUMENTS_H_
#define CERBERUS_APPS_UTILS_INCLUDE_UTILS_PROGRAM_ARGUMENTS_H_

#include <string>
#include <vector>

namespace utils {

/**
 * Helper class to manage program arguments, displaying usage, etc.
 * Only parses arguments as strings, up to owner of ProgramArguments to cast to the appropriate type
 */
class ProgramArguments {
 public:
  /**
   * \param programName Name of the program that will be displayed when streamed/outputted
   */
  explicit ProgramArguments(const std::string &programName);

  /**
   * Will print to stdout the program details/usage
   */
  void ShowUsage() const;

  /**
   * Add an argument for the program
   * \param argName name of the argument, example: file_path
   * \param argDescription some text description explaining the arugment
   * \param required true if the argument is required, false otherwise
   */
  void AddArgument(const std::string &argName,
                   const std::string &argDescription,
                   bool required);

  /**
   * Parse the command line options, assumes argc, and argv have not been modified from command line
   * \param argc the arg count (typically from main.cpp)
   * \param argv the arg vector (typically from main.cpp)
   * \return true if successfully parsed all arguments, and all required options are present
   * \return false if an unknown option was detected, or a required option was not provided
   */
  bool ParseArguments(int argc, char *argv[]);
 private:

  std::string program_name_;
  std::vector<std::string> args_;
  std::vector<std::string> descriptions_;
  std::vector<bool> required_;
  std::vector<std::string> values_;
};

}

#endif
