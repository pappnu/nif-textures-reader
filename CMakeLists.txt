project(nif-textures-reader)

# define N-API version
add_definitions(-DNAPI_VERSION=3)

include(FetchContent)

# json
FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent.git
)
FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# nifly
FetchContent_Declare(
    nifly
    GIT_REPOSITORY https://github.com/ousnius/nifly.git
    GIT_TAG main
)
FetchContent_GetProperties(nifly)
if (NOT nifly_POPULATED)
    FetchContent_Populate(nifly)
endif()
add_library(nifly STATIC
    ${nifly_SOURCE_DIR}/external/half.hpp
    ${nifly_SOURCE_DIR}/external/Miniball.hpp
    ${nifly_SOURCE_DIR}/include/Animation.hpp
    ${nifly_SOURCE_DIR}/include/BasicTypes.hpp
    ${nifly_SOURCE_DIR}/include/bhk.hpp
    ${nifly_SOURCE_DIR}/include/ExtraData.hpp
    ${nifly_SOURCE_DIR}/include/Factory.hpp
    ${nifly_SOURCE_DIR}/include/Geometry.hpp
    ${nifly_SOURCE_DIR}/include/Keys.hpp
    ${nifly_SOURCE_DIR}/include/NifFile.hpp
    ${nifly_SOURCE_DIR}/include/NifUtil.hpp
    ${nifly_SOURCE_DIR}/include/Nodes.hpp
    ${nifly_SOURCE_DIR}/include/Objects.hpp
    ${nifly_SOURCE_DIR}/include/Particles.hpp
    ${nifly_SOURCE_DIR}/include/Shaders.hpp
    ${nifly_SOURCE_DIR}/include/Skin.hpp
    ${nifly_SOURCE_DIR}/include/VertexData.hpp
    ${nifly_SOURCE_DIR}/include/KDMatcher.hpp
    ${nifly_SOURCE_DIR}/include/Object3d.hpp
    ${nifly_SOURCE_DIR}/src/Animation.cpp
    ${nifly_SOURCE_DIR}/src/BasicTypes.cpp
    ${nifly_SOURCE_DIR}/src/bhk.cpp
    ${nifly_SOURCE_DIR}/src/ExtraData.cpp
    ${nifly_SOURCE_DIR}/src/Factory.cpp
    ${nifly_SOURCE_DIR}/src/Geometry.cpp
    ${nifly_SOURCE_DIR}/src/NifFile.cpp
    ${nifly_SOURCE_DIR}/src/Nodes.cpp
    ${nifly_SOURCE_DIR}/src/Objects.cpp
    ${nifly_SOURCE_DIR}/src/Particles.cpp
    ${nifly_SOURCE_DIR}/src/Shaders.cpp
    ${nifly_SOURCE_DIR}/src/Skin.cpp
    ${nifly_SOURCE_DIR}/src/Object3d.cpp
)
target_include_directories(nifly PUBLIC ${nifly_SOURCE_DIR}/include ${nifly_SOURCE_DIR}/external)
target_compile_features(nifly PUBLIC cxx_std_17)
if(MSVC)
    target_compile_options(nifly PUBLIC "/EHsc" "/bigobj")
endif()

include_directories(${CMAKE_JS_INC})
file(GLOB SOURCE_FILES "src/main.cpp")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})

# Include N-API wrappers
execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )
string(REPLACE "\n" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
string(REPLACE "\"" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PUBLIC nifly)
