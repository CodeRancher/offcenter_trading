
CMAKE_PREFIX_PATH="${HOME}/dev/offcenter/trade/external_lib/lib/cmake/nlohmann_json;${HOME}/dev/offcenter/trade/external_lib/lib/cmake/cpprestsdk;${HOME}/dev/offcenter/trade/external_src/easyloggingpp/cmake"
EASYLOGGINGPP_ROOT="${HOME}/dev/offcenter/trade/external_lib"
EASYLOGGINGPP_USE_STATIC_LIBS="ON"
GTEST_ROOT="${HOME}/dev/offcenter/trade/external_lib"
LOG_V20_ACCESS="ON"


pushd build
cmake -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH} -DEASYLOGGINGPP_ROOT=${EASYLOGGINGPP_ROOT} -DEASYLOGGINGPP_USE_STATIC_LIBS=${EASYLOGGINGPP_USE_STATIC_LIBS} -DGTEST_ROOT=${GTEST_ROOT} -DLOG_V20_ACCESS=${LOG_V20_ACCESS} ..
#cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=ON -DLOG_V20_ACCESS:STRING=ON -DCMAKE_INSTALL_PREFIX:STRING=/home/sbrauer/dev_libs/offcenter -DCMAKE_PREFIX_PATH:PATH=/home/sbrauer/dev/offcenter/trade/external_lib/lib/cmake/nlohmann_json;/home/sbrauer/dev/offcenter/trade/external_lib/lib/cmake/cpprestsdk;/home/sbrauer/dev/offcenter/trade/external_src/easyloggingpp/cmake -DEASYLOGGINGPP_ROOT:PATH=/home/sbrauer/dev/offcenter/trade/external_lib -DGTEST_ROOT:STRING=/home/sbrauer/dev/offcenter/trade/external_lib -DEASYLOGGINGPP_USE_STATIC_LIBS:STRING=ON -G "Unix Makefiles" -DCMAKE_MODULE_PATH:PATH=/home/sbrauer/dev/offcenter/trade/external_lib/lib/cmake/nlohmann_json /home/sbrauer/dev/offcenter/trade/brokers/oanda 
make
popd