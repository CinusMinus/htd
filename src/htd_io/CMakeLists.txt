aux_source_directory(. HTD_IO_SRC_LIST)

if (BUILD_SHARED_LIBS)
    set(HTD_IO_SHARED_LIBRARY ON)
else (BUILD_SHARED_LIBS)
    set(HTD_IO_SHARED_LIBRARY OFF)
endif (BUILD_SHARED_LIBS)

configure_file("${PROJECT_SOURCE_DIR}/cmake/templates/htd_io/PreprocessorDefinitions.hpp.in"
               "${PROJECT_BINARY_DIR}/include/htd_io/PreprocessorDefinitions.hpp")

set(HTD_IO_SOVERSION_INTERFACE 0)
set(HTD_IO_SOVERSION_REVISION 0)
set(HTD_IO_SOVERSION_AGE 0)
set(HTD_IO_SOVERSION ${HTD_IO_SOVERSION_INTERFACE}.${HTD_IO_SOVERSION_REVISION}.${HTD_IO_SOVERSION_AGE})

file(GLOB_RECURSE HTD_IO_HEADER_LIST ${PROJECT_SOURCE_DIR}/include/htd_io/*.hpp)
add_library(htd_io ${HTD_IO_SRC_LIST})
target_include_directories(htd_io PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR}/include)

set_target_properties(htd_io PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    POSITION_INDEPENDENT_CODE 1
    VERSION ${HTD_IO_SOVERSION}
    SOVERSION ${HTD_IO_SOVERSION_INTERFACE}
)


# https://www.foonathan.net/2018/10/cmake-warnings/
target_compile_options(htd PRIVATE
     $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
          -Wall>
     $<$<CXX_COMPILER_ID:MSVC>:
          /W4>)

if(APPLE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")

    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -undefined dynamic_lookup")
endif(APPLE)

if(UNIX)
    set_target_properties(htd_io
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endif(UNIX)

if(MSVC)
    target_link_libraries(htd_io htd)
endif(MSVC)

install(TARGETS htd_io ARCHIVE LIBRARY DESTINATION lib)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/htd_io" DESTINATION include)
