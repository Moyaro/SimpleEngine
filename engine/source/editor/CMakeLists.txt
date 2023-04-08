#设置构建目标
set(TARGET_NAME EngineEditor)

#收集文件目录到对应变量
file(GLOB EDITOR_HEADERS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB EDITOR_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

#文件归类
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${EDITOR_HEADERS} ${EDITOR_SOURCES} ${EDITOR_RESOURCE})

add_executable(${TARGET_NAME} ${EDITOR_HEADERS} ${EDITOR_SOURCES})

add_compile_definitions("MAIN_ROOT_DIR=${MAIN_ROOT_DIR}/bin")

target_include_directories(
  ${TARGET_NAME} 
  PUBLIC $<BUILD_INTERFACE:${THIRD_PARTY_DIR}/stb>
)

target_link_libraries(${TARGET_NAME} EngineRuntime)

set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 17 OUTPUT_NAME "EngineEditor")
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "Engine")

target_compile_options(${TARGET_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/WX->")

set(POST_BUILD_COMMANDS
  COMMAND ${CMAKE_COMMAND} -E make_directory "${MAIN_ROOT_DIR}/bin"
  COMMAND echo "Copying resource files to binary directory: ${BINARY_ROOT_DIR}"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/resource" "${MAIN_ROOT_DIR}/bin/resource"
  COMMAND echo "Copying binaries to binary directory: ${BINARY_ROOT_DIR}"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "$<TARGET_FILE_DIR:${TARGET_NAME}>/" "${MAIN_ROOT_DIR}/bin"
  COMMAND echo "Copying configuration files to binary directory: ${BINARY_ROOT_DIR}"
  COMMAND ${CMAKE_COMMAND} -E copy "${ENGINE_ROOT_DIR}/${CONFIG_DIR}/${TARGET_NAME}.ini" "${MAIN_ROOT_DIR}/bin"
  COMMAND ${CMAKE_COMMAND} -E copy "${ENGINE_ROOT_DIR}/${CONFIG_DIR}/${TARGET_NAME}.ini" "$<TARGET_FILE_DIR:${TARGET_NAME}>/"
  COMMAND echo "Copying engine asset files to binary directory: ${BINARY_ROOT_DIR}${ENGINE_ASSET_DIR}"
  COMMAND ${CMAKE_COMMAND} -E remove_directory "${MAIN_ROOT_DIR}/bin/${ENGINE_ASSET_DIR}"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${ENGINE_ROOT_DIR}/${ENGINE_ASSET_DIR}" "${MAIN_ROOT_DIR}/bin/${ENGINE_ASSET_DIR}"
)

# 将命令中的路径转换为本地格式
FILE(TO_NATIVE_PATH "${ENGINE_ROOT_DIR}/${ENGINE_ASSET_DIR}" ENGINE_ASSET_DIR_NATIVE)
FILE(TO_NATIVE_PATH "${MAIN_ROOT_DIR}/bin/${ENGINE_ASSET_DIR}" BINARY_ENGINE_ASSET_DIR_NATIVE)

add_custom_command(TARGET ${TARGET_NAME} ${POST_BUILD_COMMANDS} VERBATIM)

#precompile
set(ENGINE_EDITOR_HEADS “${EDITOR_HEADERS}” PARENT_SCOPE)