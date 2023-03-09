set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-conversion")

add_executable(test_client test_client.c)
target_link_libraries(test_client
  PRIVATE client
  PUBLIC ${CRITERION}
)
add_test(
  NAME test_client
  COMMAND test_client ${CRITERION_FLAGS}
)

# add_executable(test_absolute test_absolute.c)
# target_link_libraries(test_absolute
#   PRIVATE absolute
#   PUBLIC ${CRITERION}
# )
# add_test(
#   NAME test_absolute
#   COMMAND test_absolute ${CRITERION_FLAGS}
# )

# add_executable(test_greet test_greet.c)
# target_link_libraries(test_greet
#   PRIVATE greet
#   PUBLIC ${CRITERION}
# )
# add_test(
#   NAME test_greet
#   COMMAND test_greet ${CRITERION_FLAGS}
# )

# add_executable(test_paths test_paths.c)
# target_link_libraries(test_paths
#   PRIVATE paths
#   PUBLIC ${CRITERION}
# )
# add_test(
#   NAME test_paths
#   COMMAND test_paths ${CRITERION_FLAGS}
# )
