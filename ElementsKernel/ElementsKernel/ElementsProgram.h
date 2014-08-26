/**
 * @file ElementsProgram.h
 * @brief define the class for the base Elements program
 * @date Aug 7, 2013
 * @author Pierre Dubath - The Euclid Consortium
 */

#ifndef ELEMENTSPROGRAM_H_
#define ELEMENTSPROGRAM_H_

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include "ElementsKernel/ElementsLogging.h"
#include "ElementsKernel/Exit.h"
#include "ElementsKernel/Export.h" // ELEMENTS_API

/**
 * Macro which must be used to create a main in classes
 * that derived from ElementsProgram, i.e., these derived classes
 * must end with the following line:
 *
 * 		MAIN_FOR(ElementsProgramExample)
 *
 * 	ElementsProgramExample.cpp shows how to use this macro
 */
#define MAIN_FOR(ElementsProgramName) 		    \
  int main(int argc, char* argv[]) 					        \
  {                               				        	\
    ElementsProgramName elementProgramInstance {} ;	\
    Elements::ExitCode exit_code = elementProgramInstance.run(argc, argv) ;	      \
    return static_cast<Elements::ExitCodeType>(exit_code) ;                                       \
  }

static const std::string CONF_ENV_VAR_NAME {"ELEMENTS_CONF_PATH"};


/**
 * @class ElementsProgram
 * @brief
 * 		Base class for all Elements programs
 * @details
 * 		This base class offers solutions for the common needs of
 * 		all Elements programs, such as those dealing with program
 * 		options and logging.
 */
class ElementsProgram {

public:

  /**
   * @brief
   *  This is the public entry point, i.e., the only method
   *  called from the main
   *
   * @param argc
   *   Command line argument number
   * @param argv
   *   Command line arguments
   */
  ELEMENTS_API Elements::ExitCode run(int argc, char* argv[]);

protected:

  /**
   * @brief Constructor
   */
  ElementsProgram() = default;

  /**
   * @brief Destructor
   */
  virtual ~ElementsProgram() = default;

  /**
   * @brief
   *   This methods must be used to define specific program options
   * @details
   *  This is the first method that must be implemented by all Elements programs
   *  It is called from getProgramOptions(int argc,char* argv[])
   *
   * @return
   *   A BOOST options description
   */
  virtual boost::program_options::options_description defineSpecificProgramOptions() = 0;

  /**
   * @brief
   *   This is the "main" method of all Elements programs
   * @details
   *  This is the second method that must be implemented by all Elements programs. It
   *  represents the entry point, called from run(int argc,char* argv[]).
   */
  virtual Elements::ExitCode mainMethod() = 0;

  /**
   * @brief
   *   Get the program version from svn tags
   * @details
    *
   * @return
   *   A string with the version information
   */
  virtual std::string getVersion() = 0;

  /**
   * @brief Getter
   *
   * @return
   *   The program path
   */
  const boost::filesystem::path& getProgramPath() const {
    return m_program_path;
  }

   /**
    * @brief Getter
    *
    * @return
    *   The program name
    */
  const boost::filesystem::path& getProgramName() const {
    return m_program_name;
  }

  /**
   * @brief Getter
   *
   * @return
   *   The BOOST variables_map which includes all program options.
   */
  const boost::program_options::variables_map& getVariablesMap() const {
    return m_variables_map;
  }

private:


  /**
   * This is the BOOST program options variable_map used to store all
   * program options. It is similar to a std::map but the element can be
   * of different types. See the pseudoMain() in ElementsProgramExample.cpp
   * to see how to retrieve options from this map.
   */
  boost::program_options::variables_map m_variables_map { };

  /**
   * Name of the executable (from argv[0])
   */
  boost::filesystem::path m_program_name;

  /**
   * Path of the executable (from argv[0])
   */
  boost::filesystem::path m_program_path;

  /**
   * @brief
   *   Get a default configuration file name and path, to be used if not
   *   provided as a command line option
   *
   * @return
   *   A complete name/path to the default configuration file
   */
   const boost::filesystem::path getDefaultConfigFile(
       const boost::filesystem::path & program_name) const;

  /**
   * @brief
   *   Get a default log file name and path, to be used if not
   *   provided as a command line option. By default a log file
   *
   *     ./"programName".log
   *
   *    will be returned
   *
   * @return
   *   A complete name/path to the default log file
   */
  const boost::filesystem::path getDefaultLogFile(
      const boost::filesystem::path & program_name) const;

  /**
   * @brief
   *    Strip the path from argv[0] to set the program name
   * @param argv
   *    The first element of the command line, i.e., argv[0]
   * @return
   *    A BOOST path with the program name
   */
  const boost::filesystem::path setProgramName(char* argv) const;

  /**
   * @brief
   *    Strip the name from argv[0] to set the program path
   * @param argv
   *    The first element of the command line, i.e., argv[0]
   * @return
   *    A BOOST path with the program path
   */
  const boost::filesystem::path setProgramPath(char* argv) const;

  /**
   * @brief
   *  Program setup taking care of command line options and logging
   *  initialization
   */
  void setup(int argc, char* argv[]) noexcept;

  /**
   * @brief
   *  Get the program options from the command line into the
   *  variables_map
   *
   *  @return
   *    A BOOST variable_map
   */
  const boost::program_options::variables_map getProgramOptions(int argc,
      char* argv[]);

  /**
   * @brief
   *  Log all program options
   *
   */
  void logAllOptions(std::string program_name);

};

#endif /* ELEMENTSPROGRAM_H_ */
