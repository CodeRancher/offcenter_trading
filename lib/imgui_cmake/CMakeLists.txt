
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GL3W)
add_compile_definitions(IMGUI_IMPL_OPENGL_ES2)
#add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLEW)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
#find_package(glew REQUIRED)

add_library(imgui STATIC)

target_sources(imgui
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/imgui/imgui.cpp
		${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_demo.cpp
		${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_draw.cpp
		${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_tables.cpp
		${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_widgets.cpp

		#${CMAKE_CURRENT_LIST_DIR}/imgui/backends/imgui_impl_glfw.cpp
		#${CMAKE_CURRENT_LIST_DIR}/imgui/backends/imgui_impl_opengl3.cpp

#		${CMAKE_CURRENT_LIST_DIR}/imgui/examples/libs/gl3w/GL/gl3w.c
		
#	PUBLIC
#		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/Connection.hpp>
#		$<INSTALL_INTERFACE:include/offcenter/amqp/Connection.hpp>
#	
#		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/ConnectionOptions.hpp>
#		$<INSTALL_INTERFACE:include/offcenter/amqp/ConnectionOptions.hpp>
#	
#		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/ConnectionOptionElements.hpp>
#		$<INSTALL_INTERFACE:include/offcenter/amqp/ConnectionOptionElements.hpp>
#	
#		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/Consumer.hpp>
#		$<INSTALL_INTERFACE:include/offcenter/amqp/Consumer.hpp>
#	
#		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/Helper.hpp>
#		$<INSTALL_INTERFACE:include/offcenter/amqp/Helper.hpp>
#	
#		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/Message.hpp>
#		$<INSTALL_INTERFACE:include/offcenter/amqp/Message.hpp>
#	
#		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/MessageBase.hpp>
#		$<INSTALL_INTERFACE:include/offcenter/amqp/MessageBase.hpp>
#	
#		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/Producer.hpp>
#		$<INSTALL_INTERFACE:include/offcenter/amqp/Producer.hpp>
#	
#		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/ProducerConsumerBase.hpp>
#		$<INSTALL_INTERFACE:include/offcenter/amqp/ProducerConsumerBase.hpp>
#	
#		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/URLSchemeHost.hpp>
#		$<INSTALL_INTERFACE:include/offcenter/amqp/URLSchemeHost.hpp>
#	
#		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/offcenter/amqp/AMQPException.hpp>
#		$<INSTALL_INTERFACE:include/offcenter/amqp/AMQPException.hpp>
)

#target_link_libraries(imgui
#	glfw
#	OpenGL::GL
#)

target_include_directories(imgui
	PUBLIC
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/imgui>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/imgui>"
	
		"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/imgui/backends>"
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/imgui/backends>"

		#"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/imgui/examples/libs/gl3w>"
		#"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/imgui/examples/libs/gl3w>"
)

add_executable(imgui_example_glfw_opengl3
		${CMAKE_CURRENT_LIST_DIR}/imgui/examples/example_glfw_opengl3/main.cpp
		#${CMAKE_CURRENT_LIST_DIR}/imgui/examples/libs/gl3w/GL/gl3w.c
		${CMAKE_CURRENT_LIST_DIR}/imgui/backends/imgui_impl_glfw.cpp
		${CMAKE_CURRENT_LIST_DIR}/imgui/backends/imgui_impl_opengl3.cpp

)

target_link_libraries(imgui_example_glfw_opengl3
	imgui
	glfw
	OpenGL::GL
)

target_include_directories(imgui_example_glfw_opengl3
	PUBLIC
		${CMAKE_CURRENT_LIST_DIR}/imgui
		${CMAKE_CURRENT_LIST_DIR}/imgui/backends
		${CMAKE_CURRENT_LIST_DIR}/imgui/examples/libs/gl3w
)


