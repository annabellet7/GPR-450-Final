file(
 GLOB_RECURSE GPR-450_Final_INC CONFIGURE_DEPENDS
 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
 *.h *.hpp
)

file(
 GLOB_RECURSE GPR-450_Final_SRC CONFIGURE_DEPENDS
 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
 *.c *.cpp
)
#Copies this GPR-450_Final's asset folder to bin when it is built
add_custom_target(copyAssetsFinal ALL COMMAND ${CMAKE_COMMAND} -E copy_directory
${CMAKE_CURRENT_SOURCE_DIR}/assets/
${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets/)

install(FILES ${GPR-450_Final_INC} DESTINATION include/GPR-450_Final)
add_executable(GPR-450_Final ${GPR-450_Final_SRC} ${GPR-450_Final_INC})
target_link_libraries(GPR-450_Final PUBLIC core IMGUI assimp)
target_include_directories(GPR-450_Final PUBLIC ${CORE_INC_DIR} ${stb_INCLUDE_DIR})

#Trigger asset copy when GPR-450_Final is built
add_dependencies(GPR-450_Final copyAssetsFinal)