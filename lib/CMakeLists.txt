
# Global Libraries
find_package(Boost
	1.74
	COMPONENTS program_options atomic thread system regex filesystem random chrono serialization 
)
# websocketpp  date-time

add_subdirectory(data_types)
add_subdirectory(data_types_amqp)
add_subdirectory(data_types_json)
add_subdirectory(data_types_soci)
add_subdirectory(common)
add_subdirectory(oanda_persistence_client)
add_subdirectory(trading)
add_subdirectory(trading_db)
add_subdirectory(lib2)
add_subdirectory(imgui_cmake)
