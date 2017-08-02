'''
Created on Feb 10 2017

@author: Hubert Degaudenzi


@copyright: 2012-2020 Euclid Science Ground Segment

This library is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free
Software Foundation; either version 3.0 of the License, or (at your option)
any later version.

This library is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
details.

You should have received a copy of the GNU Lesser General Public License
along with this library; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

'''

import os

from ElementsKernel.Path import getLocationsFromEnv, VARIABLE, \
    getPathFromLocations
from ElementsKernel.System import DEFAULT_INSTALL_PREFIX

def getAuxiliaryLocations(exist_only=False):

    location_list = getLocationsFromEnv(VARIABLE["auxiliary"], exist_only)

    location_list.append(os.path.join(DEFAULT_INSTALL_PREFIX, "share", "auxdir"))
    location_list.append(os.path.join(DEFAULT_INSTALL_PREFIX, "share", "aux"))

    if exist_only:
        location_list = [p for p in location_list if os.path.exists(p)]

    return location_list


def getAuxiliaryPath(file_name, raise_exception=True):
    """
    Get full path to the file name searched in the auxiliary path
    """

    location_list = getAuxiliaryLocations()

    result = getPathFromLocations(file_name, location_list)

    if not result and raise_exception:
        raise Exception("The auxiliary file \"%s\" cannot be found!", file_name)

    return result
