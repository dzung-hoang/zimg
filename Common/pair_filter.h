#pragma once

#ifndef ZIMG_PAIR_FILTER_H_
#define ZIMG_PAIR_FILTER_H_

#include <memory>
#include "zfilter.h"

namespace zimg {;

enum class PixelType;

class PairFilter final : public IZimgFilter {
	struct cache_context;
public:
	struct builder {
		IZimgFilter *first;
		IZimgFilter *second;

		unsigned first_width;
		unsigned first_height;
		PixelType first_pixel;

		unsigned second_width;
		unsigned second_height;
		PixelType second_pixel;
	};
private:
	std::unique_ptr<IZimgFilter> m_first;
	std::unique_ptr<IZimgFilter> m_second;

	ZimgFilterFlags m_first_flags;
	ZimgFilterFlags m_second_flags;

	unsigned m_first_width;
	unsigned m_first_height;
	PixelType m_first_pixel;

	unsigned m_second_width;
	unsigned m_second_height;
	PixelType m_second_pixel;

	unsigned m_first_step;
	unsigned m_second_step;

	bool m_has_state;
	bool m_in_place;
	bool m_color;

	ptrdiff_t get_cache_stride() const;

	unsigned get_cache_line_count() const;

	size_t get_cache_size_one_plane() const;

	unsigned get_num_planes() const;
public:
	PairFilter(const builder &b);

	ZimgFilterFlags get_flags() const override;

	pair_unsigned get_required_row_range(unsigned i) const override;

	pair_unsigned get_required_col_range(unsigned left, unsigned right) const override;

	unsigned get_simultaneous_lines() const override;

	unsigned get_max_buffering() const override;

	size_t get_context_size() const override;

	size_t get_tmp_size(unsigned left, unsigned right) const override;

	void init_context(void *ctx) const override;

	void process(void *ctx, const ZimgImageBuffer *src, const ZimgImageBuffer *dst, void *tmp, unsigned i, unsigned left, unsigned right) const override;
};

}

#endif // ZIMG_PAIR_FILTER_H_