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

add_executable(test_chat_utilities test_chat_utilities.c)
target_link_libraries(test_chat_utilities
  PRIVATE chat_utilities
  PUBLIC ${CRITERION}
)
add_test(
  NAME test_chat_utilities
  COMMAND test_chat_utilities ${CRITERION_FLAGS}
)

add_executable(test_server test_server.c)
target_link_libraries(test_server
  PRIVATE server
  PUBLIC ${CRITERION}
)
add_test(
  NAME test_server
  COMMAND test_server ${CRITERION_FLAGS}
)
