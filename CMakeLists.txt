# EOOS SYSTEM.
#
# @author    Sergey Baigudin, sergey@baigudin.software
# @copyright 2019, Sergey Baigudin, Embedded Team
# @license   http://embedded.team/license/

enable_language(CXX)

target_include_directories(${PROJECT_NAME}
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_sources(${PROJECT_NAME}
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/source/system.Allocator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/system.Main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/system.Object.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/system.System.cpp
)
