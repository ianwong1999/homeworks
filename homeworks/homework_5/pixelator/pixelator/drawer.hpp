#pragma once

#include "ftxui/screen/screen.hpp"
#include "pixelate_image.hpp"

#include <algorithm>
#include <string>
#include <vector>
#include <utility>

namespace pixelator {

class Drawer {
public:
	explicit Drawer(ftxui::Dimensions dim) : screen(ftxui::Screen::Create(ftxui::Dimension::Full())) {
		rows_ = dim.dimy;
		cols_ = dim.dimx * 2;

		screen = ftxui::Screen::Create(ftxui::Dimension::Fixed(cols_), ftxui::Dimension::Fixed(rows_));
	}

	int rows() const noexcept {
		return rows_;
	}

	int cols() const noexcept {
		return cols_;
	}

	Size size() const noexcept {
		return {rows_, cols_};
	}

	template<typename T>
	void Set(T&& view) {
		image_ = view.get_image();
		image_rows_ = view.rows();
		image_cols_ = view.cols();
	}

	void Draw() {
		set_image_on_screen();
		screen.Print();
	}

	std::string ToString() {
		set_image_on_screen();
		return screen.ToString();
	}

private:
	void set_image_on_screen() {
		for (int i = 0; i < image_rows_; i++) {
			for (int j = 0; j < image_cols_ * 2; j++) {
				auto& pixel = screen.PixelAt(j, i);

				const int index = i * image_cols_ + j / 2;
				pixel.background_color = image_[index];
				pixel.character = ' ';
			}
		}

	}
	int rows_;
	int cols_;
	std::vector<ftxui::Color> image_;
	int image_rows_;
	int image_cols_;
	ftxui::Screen screen;
};

}
