cmake_minimum_required(VERSION 3.12)
project(cits3003_lab6)

set(CMAKE_CXX_STANDARD 17)

add_executable(cits3003_lab6 main.cpp helpers/ShaderHelper.cpp helpers/imgui/ImGuiImpl.cpp helpers/imgui/ImGuiManager.cpp)

# Some optional flags to turn max warnings on, and also turn warnings into errors, if you feel like being pedantic
#if(MSVC)
#    target_compile_options(cits3003_lab6 PRIVATE "/W3" "/WX" "/D_CRT_SECURE_NO_WARNINGS")
#else()
#    target_compile_options(cits3003_lab6 PRIVATE "-Wextra" "-Wpedantic" "-Wall" "-Werror" "-Wno-deprecated-declarations")
#endif()


# Build and link libraries


# GLAD
add_subdirectory(lib/glad)
# end GLAD


# GLFW
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw)

if (APPLE)
    # "-framework OpenGL"
    target_link_libraries(cits3003_lab6 "-framework Cocoa" "-framework IOKit")
endif()
# end GLFW


# glm
add_subdirectory(lib/glm)
#end glm


# ImGui
add_subdirectory(lib/imgui)
#end ImGui


target_link_libraries(cits3003_lab6 glfw glad glm imgui)


# Copy executable post build
add_custom_command(TARGET cits3003_lab6
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:cits3003_lab6> ${CMAKE_SOURCE_DIR})


if (WIN32)
    # Due to symbolic links requiring higher privileges on Windows, manually create Junctions instead
    file(TO_NATIVE_PATH "${CMAKE_BINARY_DIR}/res" _dstResDir)
    file(TO_NATIVE_PATH "${CMAKE_SOURCE_DIR}/res" _srcResDir)

    # Link the res dir into where the build puts the exe
    add_custom_command(TARGET cits3003_lab6
            POST_BUILD
            COMMAND cmd.exe /c if not exist "${_dstResDir}" mklink /J "${_dstResDir}" "${_srcResDir}")

    file(TO_NATIVE_PATH "${CMAKE_BINARY_DIR}/config" _dstConfigDir)
    file(TO_NATIVE_PATH "${CMAKE_SOURCE_DIR}/config" _srcConfigDir)

    # Link the config dir into where the build puts the exe
    add_custom_command(TARGET cits3003_lab6
            POST_BUILD
            COMMAND cmd.exe /c if not exist "${_dstConfigDir}" mklink /J "${_dstConfigDir}" "${_srcConfigDir}")
else()
    # Link the res dir into where the build puts the exe
    add_custom_command(TARGET cits3003_lab6
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/res ${CMAKE_BINARY_DIR}/res)

    # Link the config dir into where the build puts the exe
    add_custom_command(TARGET cits3003_lab6
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/config ${CMAKE_BINARY_DIR}/config)
endif()