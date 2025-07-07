cmake_minimum_required(VERSION 3.5)
project(org_chart CXX)


add_executable(org_chart main.cc)
target_link_libraries(org_chart PRIVATE drogon)

include(CheckIncludeFileCXX)

check_include_file_cxx(any HAS_ANY)
check_include_file_cxx(string_view HAS_STRING_VIEW)
check_include_file_cxx(coroutine HAS_COROUTINE)
if (NOT "${CMAKE_CXX_STANDARD}" STREQUAL "")
    # Do nothing
elseif (HAS_ANY AND HAS_STRING_VIEW AND HAS_COROUTINE)
    set(CMAKE_CXX_STANDARD 20)
elseif (HAS_ANY AND HAS_STRING_VIEW)
    set(CMAKE_CXX_STANDARD 17)
else ()
    set(CMAKE_CXX_STANDARD 14)
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# ##############################################################################
# Only add subdirectories if they exist
if(EXISTS "${CMAKE_SOURCE_DIR}/third_party/drogon")
    add_subdirectory(third_party/drogon)
    target_link_libraries(${PROJECT_NAME} PRIVATE drogon)
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/third_party/jwt-cpp")
    add_subdirectory(third_party/jwt-cpp)
    target_link_libraries(${PROJECT_NAME} PRIVATE jwt-cpp)
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/third_party/libbcrypt")
    add_subdirectory(third_party/libbcrypt)
    target_link_libraries(${PROJECT_NAME} PRIVATE bcrypt)
endif()

# Remove find_package(Drogon CONFIG REQUIRED) and target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)
# if you are building Drogon from source as a submodule

if (CMAKE_CXX_STANDARD LESS 17)
    message(STATUS "use c++14")
    find_package(Boost 1.61.0 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PUBLIC Boost::boost)
elseif (CMAKE_CXX_STANDARD LESS 20)
    message(STATUS "use c++17")
else ()
    message(STATUS "use c++20")
endif ()

aux_source_directory(controllers CTL_SRC)
aux_source_directory(filters FILTER_SRC)
aux_source_directory(plugins PLUGIN_SRC)
aux_source_directory(models MODEL_SRC)
aux_source_directory(utils UTIL_SRC)

target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
                                   ${CMAKE_CURRENT_SOURCE_DIR}/models)
target_sources(${PROJECT_NAME}
               PRIVATE
               ${CTL_SRC}
               ${FILTER_SRC}
               ${PLUGIN_SRC}
               ${MODEL_SRC}
               ${UTIL_SRC})

set_property(TARGET ${PROJECT_NAME} PROPERTY ENABLE_EXPORTS ON)

# Only add test subdirectory if it exists
if(EXISTS "${CMAKE_SOURCE_DIR}/test/CMakeLists.txt")
    add_subdirectory(test)
endif()
    