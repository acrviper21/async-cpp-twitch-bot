set(TARGET_SRC 
    main.cpp
)

add_executable(${TARGET_NAME} ${TARGET_SRC}) 

target_link_libraries(${TARGET_NAME} PRIVATE
    Boost::system
    Threads::Threads
    )