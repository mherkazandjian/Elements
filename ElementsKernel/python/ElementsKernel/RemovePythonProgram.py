#
# Copyright (C) 2012-2020 Euclid Science Ground Segment
#
# This library is free software; you can redistribute it and/or modify it under
# the terms of the GNU Lesser General Public License as published by the Free
# Software Foundation; either version 3.0 of the License, or (at your option)
# any later version.
#
# This library is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
# details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this library; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
#

"""

File: python/ElementsKernel/RemovePythonProgram.py

Created on: 02/11/16
Author: Nicolas Morisset
"""

from __future__ import division, print_function
from future_builtins import *

import argparse
import os
import ElementsKernel.ProjectCommonRoutines as epcr
import ElementsKernel.Logging as log
import ElementsKernel.ParseCmakeLists as pcl

CMAKE_LISTS_FILE = 'CMakeLists.txt'

logger = log.getLogger('RemovePythonProgram')

################################################################################

def getAllFiles(program_name, module_directory, module_name):
    """
    Get all files related to a python program
    """
    delete_file_list = []
    file_name_conf = os.path.join(module_directory, 'conf', module_name, program_name) + '.conf'
    if os.path.exists(file_name_conf):
        delete_file_list.append(file_name_conf)
    file_name_cpp = os.path.join(module_directory, 'python', module_name, program_name) + '.py'
    if os.path.exists(file_name_cpp):
        delete_file_list.append(file_name_cpp)

    return delete_file_list

################################################################################

def updateCmakeListsFile(module_dir, program_name):
    """
    Update the <CMakeLists.txt> file
    """
    logger.info('Updating the <%s> file', CMAKE_LISTS_FILE)
    cmake_filename = os.path.join(module_dir, CMAKE_LISTS_FILE)

    # Cmake file already exist
    if os.path.isfile(cmake_filename):
        # Backup the file
        epcr.makeACopy(cmake_filename)
        f = open(cmake_filename, 'r')
        data = f.read()
        f.close()
        # Add the program to be removed
        cmake_object = pcl.CMakeLists(data)
        cmake_object.elements_remove_python_executable = program_name

    # Write new data
    f = open(cmake_filename, 'w')
    f.write(str(cmake_object))
    f.close()

################################################################################

def defineSpecificProgramOptions():
    """
    Define program option(s)
    """
    description = """
    This script allows you to remove all files on disk related to a python
    program. Usually you use this script when you made a typo in the program
    name when calling the <AddPythonProgram> script. The <CMakeLists.txt> file
    is updated accordingly.
    """
    from argparse import RawTextHelpFormatter

    parser = argparse.ArgumentParser(description=description,
                                     formatter_class=RawTextHelpFormatter)
    parser.add_argument('program_name', metavar='program-name',
                        type=str, help='Program name')

    return parser

################################################################################

def mainMethod(args):
    """
    Main
    """

    logger.info('#')
    logger.info('#  Logging from the mainMethod() of the RemovePythonProgram \
    script ')
    logger.info('#')

    # True: no error occured
    script_goes_on = True

    program_name = args.program_name

    # Default is the current directory
    module_dir = os.getcwd()

    logger.info('Current directory : %s', module_dir)
    logger.info('')

    # We absolutely need a Elements cmake file
    script_goes_on, module_name = epcr.isElementsModuleExist(module_dir)

    if script_goes_on:
        # Default is the current directory
        file_to_be_deleted = getAllFiles(program_name, module_dir, module_name)
        if file_to_be_deleted:
            for elt_file in file_to_be_deleted:
                logger.info('File to be deleted: %s', elt_file)
            response_key = raw_input('Do you want to continue?(y/n, default: n)')
            if response_key == 'Y' or response_key == 'y':
                epcr.removeFilesOnDisk(file_to_be_deleted)
                updateCmakeListsFile(module_dir, program_name)
        else:
            logger.info('No file found for deletion!')
            logger.info('')

        logger.info('Script over')
    else:
        logger.error('No module name found at the current directory : %s', module_dir)
        logger.error('Script stopped...')
