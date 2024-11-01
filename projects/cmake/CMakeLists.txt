cmake_minimum_required(VERSION 3.25)

set(BASE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../..)
set(ENGINE_DIRECTORY ${BASE_DIRECTORY}/../CoreEngine)

project(EndlessJourney VERSION 1.0.0)
add_subdirectory(${ENGINE_DIRECTORY}/projects/cmake CoreEngine)
add_executable(EndlessJourney)

set_target_properties(
    EndlessJourney PROPERTIES
    C_STANDARD 17
    CXX_STANDARD 23
    DEBUG_POSTFIX _debug
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH $ORIGIN
)

target_sources(
    EndlessJourney PRIVATE
    ${BASE_DIRECTORY}/source/cBlock.cpp
    ${BASE_DIRECTORY}/source/cEnemy.cpp
    ${BASE_DIRECTORY}/source/cGame.cpp
    ${BASE_DIRECTORY}/source/cInterface.cpp
    ${BASE_DIRECTORY}/source/cLevel.cpp
    ${BASE_DIRECTORY}/source/cPlayer.cpp
    ${BASE_DIRECTORY}/source/cShadow.cpp
    ${BASE_DIRECTORY}/source/application.cpp
    ${BASE_DIRECTORY}/source/main.cpp
)

target_include_directories(
    EndlessJourney PRIVATE
    ${BASE_DIRECTORY}/source
)

target_precompile_headers(
   EndlessJourney PRIVATE
   $<$<COMPILE_LANGUAGE:CXX>: ${BASE_DIRECTORY}/source/main.h>
)

target_link_libraries(
    EndlessJourney PRIVATE
    CoreEngine
)

if(CORE_EMSCRIPTEN)

    set_target_properties(
        EndlessJourney PROPERTIES
        SUFFIX .html
        RUNTIME_OUTPUT_DIRECTORY ${BASE_DIRECTORY}/executable/bin/emscripten/
    )

else()

    set_target_properties(
        EndlessJourney PROPERTIES
        SUFFIX .elf
        RUNTIME_OUTPUT_DIRECTORY ${BASE_DIRECTORY}/executable/bin/linux_x86_64/
    )

    if(NOT CORE_DEBUG)

        add_custom_command(
            TARGET EndlessJourney POST_BUILD
            COMMAND ${ENGINE_DIRECTORY}/tools/scripts/extract_symbols.sh $<TARGET_FILE:EndlessJourney>
        )

    endif()

endif()