#pragma once

#include <cmath>
#include <iostream>

#include "image.hpp"
#include "stb_image_data_view.hpp"

namespace pixelator {

class Drawer;

class PixelateImage {
public:
	explicit PixelateImage() = default;
	explicit PixelateImage(const pixelator::StbImageDataView& image, pixelator::Size smaller_size) {
		const auto factor_cols = smaller_size.cols / static_cast<float>(image.cols());
		const auto factor_rows = smaller_size.rows / static_cast<float>(image.rows());
		const auto smallest_factor = std::min(1.0f, std::min(factor_cols, factor_rows));

		rows_ = Scale(image.rows(), smallest_factor);
		cols_ = Scale(image.cols(), smallest_factor);

		image_.resize(rows_ * cols_);

		std::vector<unsigned int> tot_r(rows_ * cols_);
		std::vector<unsigned int> tot_g(rows_ * cols_);
		std::vector<unsigned int> tot_b(rows_ * cols_);
		std::vector<unsigned int> tot_cnt(rows_ * cols_);

		for (int i = 0; i < image.rows(); i++) {
			for (int j = 0; j < image.cols(); j++) {
				const auto scaled_row = Scale(i, smallest_factor);
				const auto scaled_col = Scale(j, smallest_factor);

				const int scaled_index = scaled_row * cols_ + scaled_col;

				tot_r[scaled_index] += image.at(i, j, 0);
				tot_g[scaled_index] += image.at(i, j, 1);
				tot_b[scaled_index] += image.at(i, j, 2);
				tot_cnt[scaled_index]++;
			}
		}

		for (int i = 0; i < rows_; i++) {
			for (int j = 0; j < cols_; j++) {
				const int index = i * cols_ + j;
				const auto r = static_cast<float>(tot_r[index]) / tot_cnt[index];
				const auto g = static_cast<float>(tot_g[index]) / tot_cnt[index];
				const auto b = static_cast<float>(tot_b[index]) / tot_cnt[index];

				image_[index] = ftxui::Color::RGB(std::round(r), std::round(g), std::round(b));
			}
		}
	}

	ftxui::Color at(int row, int col) const {
		return image_[row * cols_ + col];
	}

	std::vector<ftxui::Color> get_image() const {
		return image_;
	}

private:
	int Scale(int number, float factor) {
		  return static_cast<int>(number * factor);
	}

	int rows_;
	int cols_;

	std::vector<ftxui::Color> image_;

	friend Drawer;
};

}
