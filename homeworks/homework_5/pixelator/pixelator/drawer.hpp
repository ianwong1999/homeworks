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
			const auto c = col.Print(false);

			int pt1 = 0;

			while (c[pt1] != ';') pt1++;

			int pt2 = pt1 + 1;

			while (c[pt2] != ';') pt2++;

			int r = stoi(c.substr(0, pt1));
			int g = stoi(c.substr(pt1 + 1, pt2 - pt1 - 1));
			int b = stoi(c.substr(pt2 + 1));

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
