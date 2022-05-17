if(BUILD_TESTING)
        enable_testing()

        include(FetchContent)
        FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG release-1.11.0
        ) # release-1.10.0 )

        FetchContent_MakeAvailable(googletest)

        add_subdirectory(htd)
endif()
