cmake_minimum_required(VERSION 3.25)
project(CFS_SCH C)

include_directories(fsw/public_inc)
include_directories(fsw/mission_inc)
include_directories(fsw/platform_inc)
include_directories(fsw/src)
include_directories(${APPLICATION_PLATFORM_INC_LIST})

aux_source_directory(fsw/src APP_SRC_FILES)
aux_source_directory(fsw/tables APP_TABLE_FILES)

# Clocking and transaction-boundary behavior is target-specific. The default
# source uses only cFE/OSAL timers; simulation targets may select a replacement
# without adding their dependencies to the flight application sources.
if(SCH_CUSTOM_PLATFORM_SOURCE)
    list(FILTER APP_SRC_FILES EXCLUDE REGEX "/sch_custom_clock\\.c$")
    list(APPEND APP_SRC_FILES "${SCH_CUSTOM_PLATFORM_SOURCE}")
    include_directories(${SCH_CUSTOM_PLATFORM_INCLUDE_DIRS})
endif()

# Create the app module
add_cfe_app(sch ${APP_SRC_FILES})
add_cfe_tables(sch ${APP_TABLE_FILES})
