create_project_lib(SegmentGenerator)

target_include_directories(SegmentGenerator PUBLIC ../Segments)
target_link_libraries(SegmentGenerator PUBLIC Segments)

target_include_directories(SegmentGenerator PUBLIC ../Intersection)
target_link_libraries(SegmentGenerator PUBLIC Intersection)