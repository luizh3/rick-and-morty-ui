cmake_minimum_required(VERSION 3.16)

set(LIBRARY_NAME core)

add_library(${LIBRARY_NAME} SHARED
    controller/episodecontroller.cpp
    controller/episodecontroller.h
    core_global.h
    network/endpoint/episodeendpoint.h network/endpoint/episodeendpoint.cpp
    network/httpclient.h network/httpclient.cpp
    network/response/response.h network/response/response.cpp
    service/episodeservice.h service/episodeservice.cpp
    dto/episodedto.h dto/episodedto.cpp
    dto/characterdto.h dto/characterdto.cpp
    network/response/httpstatuscode.h
    network/endpoint/characterendpoint.h network/endpoint/characterendpoint.cpp

)

find_package(Qt6 REQUIRED COMPONENTS Core Network)

target_compile_definitions(core
    PRIVATE CORE_LIBRARY
)

target_include_directories(${LIBRARY_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${LIBRARY_NAME}
    PUBLIC
        Qt6::Core
    PRIVATE
        Qt6::Network
)

target_compile_features(${LIBRARY_NAME}
    PUBLIC cxx_std_17
)
