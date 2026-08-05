set(TARGET_SRC 
    main.cpp
    EnvLoader.cpp
)


add_executable(${TARGET_NAME} ${TARGET_SRC}) 

target_link_libraries(${TARGET_NAME} PRIVATE
    Boost::system
    Threads::Threads
    OpenSSL::SSL
    OpenSSL::Crypto
    )

target_include_directories(${TARGET_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/include #Tells CMake to include the directory where your header files are located from root directory
)