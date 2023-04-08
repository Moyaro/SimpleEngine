# engine、第三方库、场景资源文件夹路径设置
set(ENGINE_ROOT_DIR "${MAIN_ROOT_DIR}/engine")
set(THIRD_PARTY_DIR "${ENGINE_ROOT_DIR}/third_party")
set(ENGINE_ASSET_DIR "/asset")

set(CONFIG_DIR "configs")

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options("/MP")
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT EngineEditor)
endif()

set(vulkan_include ${THIRD_PARTY_DIR}/VulkanSDK/include)

if(WIN32)
    set(vulkan_lib ${THIRD_PARTY_DIR}/VulkanSDK/lib/Win32/vulkan-1.lib)
    set(glslangValidator_executable ${THIRD_PARTY_DIR}/VulkanSDK/bin/Win32/glslangValidator.exe)
    add_compile_definitions("ENGINE_VK_LAYER_PATH=${THIRD_PARTY_DIR}/VulkanSDK/bin/Win32")
endif()

#子目录
set(SHADER_COMPILE_TARGET EngineShaderCompile)
add_subdirectory(shader)
add_subdirectory(source/editor)
add_subdirectory(source/runtime)
add_subdirectory(third_party)

add_subdirectory(source/meta_parser)

set(CODEGEN_TARGET "EnginePreCompile")
include(source/precompile/precompile.cmake)
set_target_properties("${CODEGEN_TARGET}" PROPERTIES FOLDER "Engine" )
add_dependencies(EngineRuntime "${CODEGEN_TARGET}")
add_dependencies("${CODEGEN_TARGET}" "EngineParser")

