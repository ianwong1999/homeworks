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
		for (int i = 0; i < image_rows_; i++) {
			for (int j = 0; j < image_cols_ * 2; j++) {
				auto& pixel = screen.PixelAt(j, i);

				const int index = i * image_cols_ + j / 2;
				pixel.background_color = image_[index];
				pixel.character = ' ';
			}
		}
		screen.Print();
	}

	std::string ToString() const {
		std::string res;

		res.reserve(image_.size() * 3);

		for (const auto& col : image_) {
			uint32_t val = *reinterpret_cast<const uint32_t*>(&col);

			int r = (val >> 16) & 255;
			int g = (val >> 8) & 255;
			int b = val & 255;

			res += static_cast<unsigned char>(r);
			res += static_cast<unsigned char>(g);
			res += static_cast<unsigned char>(b);
		}

		return res;
	}

private:
	int rows_;
	int cols_;
	std::vector<ftxui::Color> image_;
	int image_rows_;
	int image_cols_;
	ftxui::Screen screen;
};

}
