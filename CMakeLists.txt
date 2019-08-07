# EOOS SYSTEM.
#
# @author    Sergey Baigudin, sergey@baigudin.software
# @copyright 2019, Sergey Baigudin, Embedded Team
# @license   http://embedded.team/license/

target_include_directories(eoos
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_sources(eoos
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/source/system.Allocator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/system.Main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/system.Object.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/system.System.cpp
)
