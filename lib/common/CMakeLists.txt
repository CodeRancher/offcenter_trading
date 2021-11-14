
add_library(offcenter_trading_common "")

target_sources(offcenter_trading_common
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src/Utility.cpp
		${CMAKE_CURRENT_LIST_DIR}/src/Logging.cpp
)

target_include_directories(offcenter_trading_common
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/include
		

)

if(ENABLE_UNIT_TESTS)
    add_subdirectory(test)
endif()

