enable_testing()

find_package(GTest REQUIRED)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Set the build type to Debug to include debug symbols
set(CMAKE_BUILD_TYPE Debug)

# Add debug flags to the compiler
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

add_executable(unit_tests
# TODO: Añadan acá todos los archivos de pruebas
    test_Tablero.cpp
    test_Estados.cpp
    test_JugadorDificil.cpp
# TODO: Añadan acá el código fuente de su proyecto. Por ejemplo:
    ../src/Tablero.cpp

    ../src/EstadoJuego.cpp
    ../src/JugadorHumano.cpp
    ../src/JugadorFacil.cpp
    ../src/JugadorDificil.cpp
)

target_link_libraries(unit_tests
    GTest::gtest
    GTest::gtest_main)

target_include_directories(unit_tests PUBLIC ${INCLUDE_DIR})

add_test(AllTests unit_tests)
