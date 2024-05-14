cmake_minimum_required(VERSION 3.20)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")
set(ASSETS_DEST_DIR "${CMAKE_BINARY_DIR}/assets")


option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(CMakeSFMLProject 
    src/main.cpp
    src/Game.cpp
)
target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics)

if(WIN32)
    add_custom_command(
        TARGET CMakeSFMLProject PRE_BUILD
        COMMENT "Copy OpenAL DLL"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll"
                $<TARGET_FILE_DIR:CMakeSFMLProject>
        VERBATIM)
endif()

# Copy the assets to the build directory
# add_custom_command(
#   TARGET CMakeSFMLProject PRE_BUILD
#   COMMAND ${CMAKE_COMMAND} -E make_directory ${ASSETS_DEST_DIR}
# )
# add_custom_command(
#   TARGET CMakeSFMLProject PRE_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_DIR} ${ASSETS_DEST_DIR}
#   COMMENT "Copying assets"
# )

#install(TARGETS CMakeSFMLProject RUNTIME DESTINATION bin)
