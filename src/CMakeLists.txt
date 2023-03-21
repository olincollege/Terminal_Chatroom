add_library(client client.c client.h)
add_library(server server.c server.h)
add_library(chat_utilities chat_utilities.c chat_utilities.h)

add_executable(client_exec client_exec.c)
target_link_libraries(client_exec client chat_utilities)

add_executable(server_exec server.c)
