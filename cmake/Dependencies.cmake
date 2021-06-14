cmake_minimum_required(VERSION 3.12)
# 3.12: target CURL::libcurl

if (CURL_DIR)
    set(PC_CURL_INCLUDE_DIRS "${CURL_DIR}/include")
    set(PC_CURL_LIBRARY_DIRS "${CURL_DIR}/lib")
endif()
find_package(CURL REQUIRED)
unset(PC_CURL_INCLUDE_DIRS)
unset(PC_CURL_LIBRARY_DIRS)
