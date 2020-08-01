cmake_minimum_required(VERSION 3.10)

set(my_project killoffer)

project(${my_project} C CXX)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/base BASE_SRC)
#aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/test TEST_SRC)
aux_source_directory(nowcoder NOWCODER_SRC)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
        ${SRC} ${BASE_SRC} ${TEST_SRC}
        ${NOWCODER_SRC})