/**
 * @file %(FILE)s
 * @date %(DATE)s
 * @author %(AUTHOR)s
 */

#include <map>
#include <string>

#include <boost/program_options.hpp>
#include "ElementsKernel/ProgramHeaders.h"

namespace po = boost::program_options;

static Elements::Logging logger = Elements::Logging::getLogger("%(PROGRAMNAME)s");

class %(PROGRAMNAME)s : public Elements::Program {

public:

  po::options_description defineSpecificProgramOptions() override {
    po::options_description options {};
    //
    // !!! Implement the program options here !!!
    //
    return options;
  }

  Elements::ExitCode mainMethod(std::map<std::string, po::variable_value>& args) override {

    Elements::Logging logger = Elements::Logging::getLogger("%(PROGRAMNAME)s");

    logger.info("#");
    logger.info("# Entering mainMethod()");
    logger.info("#");

    //
    // !!! Implement you program here !!!
    //

    logger.info("#");
    logger.info("# Exiting mainMethod()");
    logger.info("#");

    return Elements::ExitCode::OK;
  }

};

MAIN_FOR(%(PROGRAMNAME)s)



