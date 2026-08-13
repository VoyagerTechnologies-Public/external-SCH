###########################################################
#
# SCH App platform build setup
#
# This file is evaluated as part of the "prepare" stage
# and can be used to set up prerequisites for the build,
# such as generating header files
#
###########################################################

# The list of header files that control the SCH configuration
set(SCH_PLATFORM_CONFIG_FILE_LIST
  sch_msgids.h
  sch_platform_cfg.h
)

generate_configfile_set(${SCH_PLATFORM_CONFIG_FILE_LIST})
