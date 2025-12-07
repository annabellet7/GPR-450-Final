file(
 GLOB_RECURSE CORE_INC CONFIGURE_DEPENDS
 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
 *.h *.hpp
)

file(
 GLOB_RECURSE CORE_SRC CONFIGURE_DEPENDS
 RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
 *.c *.cpp
)

set(CORE_INC_DIR
 ${CMAKE_CURRENT_SOURCE_DIR}
 CACHE PATH "CORE INCLUDE SOURCE PATH"
)

add_library(core STATIC ${CORE_SRC} ${CORE_INC} "gorp/hierarchyNode.h" "gorp/hierarchyNode.cpp"   "gorp/htrLoader.h" "gorp/htrLoader.cpp"    "gorp/clipCtrl.h" "gorp/clipCtrl.cpp" "gorp/keyframe.cpp" "gorp/keyframe.h"  "gorp/hierarchy.h" "gorp/hierarchy.cpp" "gorp/hierarchyState.h" "gorp/hierarchyState.cpp" "gorp/transform.h" "gorp/transform.cpp")

find_package(OpenGL REQUIRED)

target_link_libraries(core PUBLIC IMGUI assimp glm)

install (TARGETS core DESTINATION lib)
install (FILES ${CORE_INC} DESTINATION include/core)

