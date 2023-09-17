#include "pixelator/drawer.hpp"

#include <gtest/gtest.h>
#include <ftxui/screen/color.hpp>
#include <ftxui/screen/screen.hpp>

namespace {
using pixelator::Drawer;
using pixelator::Image;
using pixelator::Size;
}  // namespace


TEST(DrawerValidationTest, SetFromImage) {
  Image image{Size{1, 2}};
  image.at(0, 0) = ftxui::Color::Black;
  image.at(0, 1) = ftxui::Color::Red;
  Drawer drawer{ftxui::Dimension::Fixed(1)};
  drawer.Set(image);
  EXPECT_EQ(drawer.ToString(),
            std::string{"\x1B[39m\x1B[40m \x1B[39m\x1B[49m"});
}
