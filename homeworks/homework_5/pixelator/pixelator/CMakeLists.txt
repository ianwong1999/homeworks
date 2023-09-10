# TODO: Add your libraries here
# You must have the following libraries:
# - stb_image_data_view
# - drawer
# - image
# - pixelate_image


add_library(stb_image_data_view INTERFACE)
target_sources(stb_image_data_view INTERFACE stb_image_data_view.hpp)
target_link_libraries(stb_image_data_view INTERFACE cxx_setup ftxui::screen)
target_link_libraries(stb_image_data_view INTERFACE cxx_setup stb)

add_library(drawer INTERFACE)
target_sources(drawer INTERFACE drawer.hpp)
target_link_libraries(drawer INTERFACE cxx_setup ftxui::screen)
target_link_libraries(drawer INTERFACE cxx_setup stb)

add_library(image INTERFACE)
target_sources(image INTERFACE image.hpp)
target_link_libraries(image INTERFACE cxx_setup ftxui::screen)
target_link_libraries(image INTERFACE cxx_setup stb)

add_library(pixelate_image INTERFACE)
target_sources(pixelate_image INTERFACE pixelate_image.hpp)
target_link_libraries(pixelate_image INTERFACE cxx_setup ftxui::screen)
target_link_libraries(pixelate_image INTERFACE cxx_setup stb)


include_directories(${PROJECT_SOURCE_DIR}/pixelator)


if(BUILD_TESTING)
	include(GoogleTest)
  # TODO: Add your tests executable with all your tests here
  # Name it pixelator_tests.
  # Also use gtest_discover_tests(pixelator_tests)
  # to register them with CTest
endif()
