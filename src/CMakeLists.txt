find_package(PkgConfig REQUIRED)
pkg_check_modules(FUSE3 REQUIRED fuse3)

include_directories(SYSTEM ${FUSE3_INCLUDE_DIR})

set(SOURCE_FILES
        fuse_oper.c)

add_library(safst-core ${SOURCE_FILES})
target_link_libraries(safst-core ${FUSE3_LIBRARIES})

add_executable(safst main.c)
target_link_libraries(safst safst-core ${FUSE3_LIBRARIES})