cmake_minimum_required(VERSION 3.22)

project(TerminalChatroom
  VERSION 1.0
  LANGUAGES C
)

set(CMAKE_C_STANDARD 17)

set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic -Wshadow -Wconversion -Wunreachable-code")
set(CMAKE_C_CLANG_TIDY "clang-tidy")
set(CMAKE_C_CLANG_TIDY
  clang-tidy;
  -header-filter=.;
  -checks=*,-llvmlibc-restrict-system-libc-headers,-llvm-header-guard,-altera*,-cert-err34-c,-cppcoreguidelines-init-variables;
)

add_subdirectory(src)

include(CTest)
find_library(CRITERION criterion REQUIRED)
set(CRITERION_FLAGS --verbose -j1)

add_subdirectory(test)
