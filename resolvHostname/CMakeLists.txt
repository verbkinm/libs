cmake_minimum_required(VERSION 3.5)

project(ANSI_C LANGUAGES C)

add_executable(ANSI_C main.c)

include(GNUInstallDirs)
install(TARGETS ANSI_C
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
