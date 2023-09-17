#pragma once

#include <vector>

#include "ftxui/screen/color.hpp"
#include "util.h"

namespace pixelator {

class Image {
public:
	explicit Image() : rows_(0), cols_(0) {};
	explicit Image(int row, int col) {
		image_.resize(row * col);
		rows_ = row;
		cols_ = col;
	}

	explicit Image(Size size) {
		image_.resize(size.rows * size.cols);
		rows_ = size.rows;
		cols_ = size.cols;
	}

	Size size() const noexcept {
		return {rows_, cols_};
	}

	int rows() const noexcept {
		return rows_;
	}

	int cols() const noexcept {
		return cols_;
	}

	bool empty() const noexcept {
		return rows_ == 0 || cols_ == 0;
	}

	ftxui::Color& at(int row, int col) {
		return image_[row * cols_ + col];
	}

	const ftxui::Color& at(int row, int col) const {
		return image_[row * cols_ + col];
	}

	std::vector<ftxui::Color> get_image() const {
		return image_;
	}

private:
	std::vector<ftxui::Color> image_;
	int rows_;
	int cols_;
};


}
