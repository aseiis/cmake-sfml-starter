cmake_minimum_required(VERSION 3.20)
project(CMakeSFMLProject LANGUAGES CXX)

# copy_assets macro
macro(copy_assets srcDir destDir)
  message(STATUS "Copying assets from ${srcDir} to ${destDir}")

  # Ensure the destination directory exists.
  file(MAKE_DIRECTORY ${destDir})

  # Copy all files and directories recursively.
  # Using GLOB_RECURSE to handle subdirectories as well.
  file(GLOB_RECURSE assetsToCopy RELATIVE ${srcDir} "${srcDir}/*")

  foreach(asset ${assetsToCopy})
      # Compute source and destination paths.
      set(src "${srcDir}/${asset}")
      set(dst "${destDir}/${asset}")

      # Check if the destination file/directory already exists.
      if(NOT EXISTS "${dst}")
          # Check if current asset is a directory.
          if(IS_DIRECTORY "${src}")
              # Make directory at the destination.
              file(MAKE_DIRECTORY "${dst}")
          else()
              # Copy file to destination.
              file(COPY "${src}" DESTINATION "${destDir}/${asset}")
          endif()
      else()
          message(STATUS "Skipping existing asset: ${dst}")
      endif()
  endforeach()
endmacro(copy_assets)

# Example usage: adjust src and dest directories as required.
copy_assets("${CMAKE_SOURCE_DIR}/assets" "${CMAKE_BINARY_DIR}/assets")

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
