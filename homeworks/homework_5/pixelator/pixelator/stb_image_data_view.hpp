#pragma once

#include "ftxui/screen/color.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "util.h"

#include <filesystem>

namespace {
	static constexpr auto kLoadAllChannels{0};
}

namespace pixelator {

class StbImageDataView {
public:
	explicit StbImageDataView() noexcept = default;
	explicit StbImageDataView(std::filesystem::path p) {
		image_ = stbi_load(p.c_str(), &cols_, &rows_, &channels_, kLoadAllChannels);
	}

	StbImageDataView(const StbImageDataView&) = delete;
	StbImageDataView& operator=(const StbImageDataView&) = delete;

	StbImageDataView(StbImageDataView&& view) {
		image_ = view.image_;
		rows_ = view.rows_;
		cols_ = view.cols_;
		channels_ = view.channels_;

		view.image_ = nullptr;
	}

	StbImageDataView& operator=(StbImageDataView&& view) {
		if (image_ != nullptr) stbi_image_free(image_);

		image_ = view.image_;
		rows_ = view.rows_;
		cols_ = view.cols_;
		channels_ = view.channels_;

		view.image_ = nullptr;
		return *this;
	}

	~StbImageDataView() {
		if (image_ == nullptr) return;
		stbi_image_free(image_);
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

	ftxui::Color at(int row, int col) const {
		const int pt = channels_ * (row * cols_ + col);
		return ftxui::Color::RGB(image_[pt], image_[pt + 1], image_[pt + 2]);
	}

	unsigned char at(int row, int col, int channel) const {
		const int pt = channels_ * (row * cols_ + col) + channel;
		return image_[pt];
	}

private:
	unsigned char* image_;
	int rows_;
	int cols_;
	int channels_;

};


}
