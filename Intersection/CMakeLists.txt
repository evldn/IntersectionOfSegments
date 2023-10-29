create_project_lib(Intersection)
target_include_directories(Intersection PUBLIC ../Segments)
target_link_libraries(Intersection PUBLIC Segments)

target_include_directories(Intersection PUBLIC ../AVL-Tree)
target_link_libraries(Intersection PUBLIC AVL-Tree)

target_include_directories(Intersection PUBLIC ../TwoThree-Tree)
target_link_libraries(Intersection PUBLIC TwoThree-Tree)