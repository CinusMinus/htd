aux_source_directory(. HTD_CLI_SRC_LIST)

list(REMOVE_ITEM HTD_CLI_SRC_LIST "main.cpp")

if (BUILD_SHARED_LIBS)
    set(HTD_CLI_SHARED_LIBRARY ON)
else (BUILD_SHARED_LIBS)
    set(HTD_CLI_SHARED_LIBRARY OFF)
endif (BUILD_SHARED_LIBS)

configure_file("${PROJECT_SOURCE_DIR}/cmake/templates/htd_cli/PreprocessorDefinitions.hpp.in"
               "${PROJECT_BINARY_DIR}/include/htd_cli/PreprocessorDefinitions.hpp")

set(HTD_CLI_SOVERSION_INTERFACE 0)
set(HTD_CLI_SOVERSION_REVISION 0)
set(HTD_CLI_SOVERSION_AGE 0)
set(HTD_CLI_SOVERSION ${HTD_CLI_SOVERSION_INTERFACE}.${HTD_CLI_SOVERSION_REVISION}.${HTD_CLI_SOVERSION_AGE})

file(GLOB_RECURSE HTD_CLI_HEADER_LIST ${PROJECT_SOURCE_DIR}/include/htd_cli/*.hpp)
add_library(htd_cli ${HTD_CLI_SRC_LIST})

target_include_directories(htd_cli PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR}/include)

set_target_properties(htd_cli PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    POSITION_INDEPENDENT_CODE 1
    VERSION ${HTD_CLI_SOVERSION}
    SOVERSION ${HTD_CLI_SOVERSION_INTERFACE}
)

# https://www.foonathan.net/2018/10/cmake-warnings/
target_compile_options(htd_cli PRIVATE
     $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
          -Wall>
     $<$<CXX_COMPILER_ID:MSVC>:
          /W4>)

if(APPLE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
endif(APPLE)


if(UNIX)
    set_target_properties(htd_cli
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endif(UNIX)

install(TARGETS htd_cli ARCHIVE LIBRARY DESTINATION lib)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/htd_cli" DESTINATION include)
