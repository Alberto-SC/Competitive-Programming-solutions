#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <vector>
using ld = long double;

struct P {
	ld x, y;
};

const ld pi = acos(-1L);
const P red{cos(-pi / 3), sin(-pi / 3)};
const P green{cos(pi / 3), sin(pi / 3)};
const P blue{-1, 0};
const std::array<P, 4> endpoints{{red, green, blue, {0, 0}}};

struct Position {
	P p;
	ld alpha;

	friend std::istream &operator>>(std::istream &i, Position &s) {
		return i >> s.p.x >> s.p.y >> s.alpha;
	}
};

struct Params {
	int pixels;
	ld theta; // total view angle of the camera
};

std::string print(ld x) {
	char buf[100];
	sprintf(buf, "%.10Lf", x);
	std::string s(buf);
	while(s.back() == '0') s.pop_back();
	if(s.back() == '.') s.pop_back();
	return s;
}

using Pixel = std::array<ld, 3>;
using Image = std::vector<Pixel>;
std::ostream &operator<<(std::ostream &o, const Image &image) {
	// o << std::fixed;
	// o << std::setprecision(8);
	for(auto &pixel : image)
		o << print(pixel[0]) << ' ' << print(pixel[1]) << ' ' << print(pixel[2]) << '\n';
	return o;
}

// a ray to a colour-endpoint
struct Ray {
	ld angle;
	int colour; /* -1 for black */
};
using Spectrum = std::vector<Ray>;

std::pair<Spectrum, bool> get_spectrum(Position s) {
	std::array<ld, 4> angles;
	for(int i = 0; i < 4; ++i) angles[i] = atan2(endpoints[i].y - s.p.y, endpoints[i].x - s.p.x);

	// check that all angles are in a range of pi
	auto copy = angles;
	std::sort(copy.begin(), copy.end());
	bool good = false;
	for(int i = 0; i < 4; ++i) {
		auto diff = copy[(i + 1) % 4] - copy[i];
		while(diff < 0) diff += 2 * pi;
		if(diff >= pi) good = true;
	}
	if(!good) {
		std::cerr << "The four interesting points span a range more than pi!\n";
		return {{}, true};
	}

	// force all angles to be within pi of each other
	// this will need hardening for contestant input
	std::array<ld, 4>::iterator min_pos, max_pos;
	while(true) {
		max_pos = std::max_element(angles.begin(), angles.end());
		min_pos = std::min_element(angles.begin(), angles.end());
		if(*max_pos - *min_pos > pi) {
			*min_pos += 2 * pi;
		} else
			break;
	}

	int first_colour = min_pos - angles.begin();
	int last_colour  = max_pos - angles.begin();
	assert(first_colour != 3);
	assert(last_colour != 3);

	// check if we can see two colours only
	if(first_colour == (last_colour + 1) % 3) {
		return {{{*min_pos, first_colour}, {angles[3], last_colour}, {*max_pos, -1}}, false};
	} else {
		// we can see three colours
		int middle_colour = 3 - first_colour - last_colour;
		ld middle_angle   = angles[middle_colour];
		if(middle_angle > angles[3])
			// middle segment coverst last colour
			return {{{*min_pos, first_colour},
			         {angles[3], middle_colour},
			         {middle_angle, last_colour},
			         {*max_pos, -1}},
			        false};
		else
			return {{{*min_pos, first_colour},
			         {middle_angle, middle_colour},
			         {angles[3], last_colour},
			         {*max_pos, -1}},
			        false};
	}
}

std::pair<Image, bool> make_image(Params params, Position position) {
	auto tmp       = get_spectrum(position);
	auto &spectrum = tmp.first;
	if(tmp.second) return {{}, true};

	// std::cerr << "spectrum:\n";
	// for(auto x : spectrum) std::cerr << x.angle << " " << x.colour << '\n';

	auto angle_per_pixel = params.theta / params.pixels;
	Image image(params.pixels, {{0, 0, 0}});

	auto it      = spectrum.begin();
	ld cur_angle = position.alpha - params.theta / 2;
	while(cur_angle > it->angle - pi) cur_angle -= 2 * pi;
	while(cur_angle < it->angle - pi) cur_angle += 2 * pi;
	int cur_colour = -1;
	for(int i = 0; i < params.pixels; ++i) {
		auto next_angle = cur_angle + angle_per_pixel;
		for(; it != spectrum.end() && it->angle < next_angle; ++it) {
			if(cur_colour != -1) image[i][cur_colour] = (it->angle - cur_angle) / angle_per_pixel;
			cur_angle                                 = it->angle;
			cur_colour                                = it->colour;
		}

		if(cur_colour != -1) image[i][cur_colour] = (next_angle - cur_angle) / angle_per_pixel;
		cur_angle                                 = next_angle;
	}

	// reverse the image, to obtain a left to right picture
	reverse(image.begin(), image.end());

	return {image, false};
}

struct Input {
	Params params;
	Image image;
	friend std::istream &operator>>(std::istream &i, Input &input) {
		i >> input.params.pixels >> input.params.theta;
		input.image.resize(input.params.pixels);
		for(auto &pixel : input.image)
			for(auto &v : pixel) i >> v;
		return i;
	}
};

// return the maximal absolute value of intensity differences
ld compare_images(const Image &i1, const Image &i2) {
	assert(i1.size() == i2.size());
	ld max_diff = 0;
	for(size_t i = 0; i < i1.size(); ++i) {
		for(int j = 0; j < 3; ++j) max_diff = std::max(max_diff, std::abs(i1[i][j] - i2[i][j]));
	}
	return max_diff;
}
