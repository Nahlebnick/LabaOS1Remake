add_executable(Creator)
target_sources(Creator PRIVATE creator/creator.cpp)

add_executable(Reporter)
target_sources(Reporter PRIVATE reporter/reporter.cpp)

add_executable(Main)
target_sources(Main PRIVATE main/main.cpp)

target_link_libraries(Reporter PRIVATE MyLib)
target_link_libraries(Creator PRIVATE MyLib)
target_link_libraries(Main PRIVATE MyLib)