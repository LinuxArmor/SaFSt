find_package(PkgConfig REQUIRED)
pkg_check_modules(FUSE3 REQUIRED fuse3) # Filesystem
find_library(LEVELDB leveldb) # LevelDB for caching data

if (NOT LEVELDB)
    message(FATAL_ERROR "LevelDB is missing")
endif()

include_directories(SYSTEM ${FUSE3_INCLUDE_DIR})

set(SOURCE_FILES
        fuse_oper.c fuse_oper.h watcher.c watcher.h cache.c cache.h fs.c fs.h)

add_library(safst-core ${SOURCE_FILES})
target_link_libraries(safst-core ${FUSE3_LIBRARIES} ${LEVELDB})

add_executable(safst main.c)
target_link_libraries(safst safst-core ${FUSE3_LIBRARIES})