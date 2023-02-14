add_executable(hello hello.c)

add_library(string_utils
  string_utils.c string_utils.h
)

add_library(absolute
  absolute.c absolute.h
)

add_library(greet greet.c greet.h)

add_executable(run_greet run_greet.c)
target_link_libraries(run_greet
  PRIVATE greet
)

add_library(paths paths.c paths.h)

add_executable(run_paths run_paths.c)
target_link_libraries(run_paths
  PRIVATE paths
)
