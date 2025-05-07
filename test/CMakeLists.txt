if(BUILD_TESTING)
        enable_testing()

        include(FetchContent)
        FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG v1.17.0
        ) # v1.17.0 )

        FetchContent_MakeAvailable(googletest)

        add_subdirectory(htd)
endif()
