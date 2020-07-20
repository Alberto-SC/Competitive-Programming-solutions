#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

using ld    = long double;
using Pixel = array<ld, 3>;
using Image = vector<Pixel>;
const ld pi = acos(-1.0L);

// 0,1,2 for red,green,blue
// -1 for black
using Colour = int;

// 0,1,2 for rgb, 3 for the black part before first colour
using ColourCount = array<ld, 4>;

struct Params {
	int pixels;
	ld theta;
};

struct Input {
	Params params;
	Image image;
};

istream &operator>>(istream &i, Input &input) {
	i >> input.params.pixels >> input.params.theta;
	input.image.resize(input.params.pixels);
	for(auto &pixel : input.image)
		for(auto &v : pixel) i >> v;
	return i;
}

ColourCount get_colourcount(const Input &input) {
	ColourCount cs{{0, 0, 0}};
	bool has_seen_colour = false;
	ld angle_per_pixel   = input.params.theta / input.params.pixels;
	// cerr << "angle per pixel " << angle_per_pixel << '\n';

	int coloured_pixels = 0;
	for(auto &pixel : input.image) {
		for(int i = 0; i < 3; ++i) cs[i] += pixel[i] * angle_per_pixel;
		auto sum  = pixel[0] + pixel[1] + pixel[2];

		if(!has_seen_colour) cs[3] += (1 - sum) * angle_per_pixel;

		if(sum > 0) has_seen_colour = true, ++coloured_pixels;
	}

	assert(coloured_pixels >= 2);

	return cs;
}

// return the left colour that is completely visible
// and the right colour that is completely visible
array<int, 2> get_fully_visible2(const Input &input, const ColourCount &cc, int &leftmost) {
	leftmost = -1;
	// first determine the left to right order in which we see colours in the image
	vector<int> order;
	for(auto &p : input.image) {
		auto numc = count_if(p.begin(), p.end(), [](ld x) { return x > 0; });
		// skip black pixels
		if(numc == 0) continue;

		int c1 = find_if(p.begin(), p.end(), [](ld x) { return x > 0; }) - p.begin();
		int c2 = find_if(p.begin() + c1 + 1, p.end(), [](ld x) { return x > 0; }) - p.begin();

		// if all 3 colours, we must be somewhere in the middle of the picture
		if(numc == 3) {
			assert(!order.empty());
			// trick to get the remaining coordinate, since they sum to 0+1+2=3
			if(c1 == order.back()) c1 = 3 - c2 - order.back();
			if(c2 == order.back()) c2 = 3 - c1 - order.back();
			// cerr << "numc = 3\n";
			--numc;
		}

		// if 1 colour, its easy
		if(numc == 1) {
			if(order.empty() || order.back() != c1) order.push_back(c1);
		}
		if(numc == 2) {
			// cerr << "numc = 2 " << c1 << ' ' << c2 << "\n";
			// if we have seen one, and not the other, it's still easy
			if(!order.empty()) {
				if(order.back() == c1) {
					order.push_back(c2);
					continue;
				}
				if(order.back() == c2) {
					order.push_back(c1);
					continue;
				}
			}
			// cerr << "pixel: " << p[c1] << ' ' << p[c2] << endl;
			// cerr << "total: " << cc[c1] << ' ' << cc[c2] << endl;

			// both colours are new!
			// exactly one can be fully seen
			// there is only one sensible order for these two colours.

			if((c1 + 1) % 3 == c2)
				order.push_back(c1), order.push_back(c2);
			else
				order.push_back(c2), order.push_back(c1);
		}
	}

	leftmost = order.front();

	// cerr << "ORDER: ";
	// for(auto x : order) cerr << x << ", ";
	// cerr << endl;

	// if two can be seen, we have full vision of both
	if(order.size() == 2) return {{order[0], order[1]}};

	assert(order.size() == 3);

	// we can fully see the middle colour, and the larger of the other two colours
	if(cc[order[0]] > cc[order[2]])
		return {{order[0], order[1]}};
	else
		return {{order[1], order[2]}};
}

struct Point {
	ld x, y;
};
// angle in radians, anticlockwise
Point rotate(Point p, int count) {
	ld angle                 = 0;
	if(count % 3 == 1) angle = 2 * pi / 3;
	if(count % 3 == 2) angle = -2 * pi / 3;
	Point ans = {cos(angle) * p.x - sin(angle) * p.y, sin(angle) * p.x + cos(angle) * p.y};
	// cerr << "rotate " << angle << ": " << ans.x << ", " << ans.y << '\n';
	return ans;
}

Point get_blue_middle(ld angle, bool bottom) {
	Point ans = {-0.5, 1 / ld(2) / tan(angle) * (bottom ? -1 : 1)};
	// cerr << "blue middle " << angle << ", " << bottom << ": " << ans.x << ", " << ans.y << '\n';
	return ans;
}

const ld eps = 1e-8;
Point intersect_circles(Point m1, Point m2) {
	auto a = m1.x, b = m1.y, c = m2.x, d = m2.y;
	auto divisor = (a - c) * (a - c) + (b - d) * (b - d);

	// cerr << "divisor: " << divisor << '\n';

	// this will happen if both circles coincide
	if(divisor < eps) return {2 * m1.x, 2 * m1.y};

	auto numerator = 2 * (b * c - a * d);
	Point p        = {(b - d) * numerator / divisor, -(a - c) * numerator / divisor};
	// cerr << "distance to m1: " << (p.x - a) * (p.x - a) + (p.y - b) * (p.y - b)
	//<< " norm m1: " << a * a + b * b << endl;
	// cerr << "distance to m2: " << (p.x - c) * (p.x - c) + (p.y - d) * (p.y - d)
	//<< " norm m2: " << c * c + d * d << endl;
	return p;
}

ld get_direction_angle(Params params, int leftmost, ld black_leader, Point pos) {
	// cerr << "get direction angle: colour " << leftmost << " leader: " << black_leader << endl;
	Point endpoint{-1, 0};
	endpoint = rotate(endpoint, leftmost + 1);
	// cerr << "endpoint: " << endpoint.x << ", " << endpoint.y << endl;
	ld left_angle  = atan2(endpoint.y - pos.y, endpoint.x - pos.x);
	ld begin_angle = left_angle + black_leader;
	ld alpha       = begin_angle - params.theta / 2;
	// cerr << "first_colour_angle: " << left_angle << ", begin_angle: " << begin_angle
	//<< ", alpha: " << alpha << endl;
	if(alpha > pi) alpha -= 2 * pi;
	if(alpha < -pi) alpha += 2 * pi;
	return alpha;
}

int main() {
	cout << fixed << setprecision(10);
	cerr << fixed << setprecision(10);

	Input input;
	cin >> input;
	// cerr << boolalpha;

	auto colourcount = get_colourcount(input);

	int leftmost;
	auto fully_visible = get_fully_visible2(input, colourcount, leftmost);

	// cerr << "fully visible: " << fully_visible[0] << ' ' << fully_visible[1] << endl;

	// Get the centers of the two circles.
	Point m1 = rotate(get_blue_middle(colourcount[fully_visible[0]], true), fully_visible[0] + 1);
	Point m2 = rotate(get_blue_middle(colourcount[fully_visible[1]], false), fully_visible[1] + 1);

	// cerr << "m1: " << m1.x << ' ' << m1.y << '\n';
	// cerr << "m2: " << m2.x << ' ' << m2.y << '\n';

	// intersect the circles to get the answer
	auto ans = intersect_circles(m1, m2);

	cout << ans.x << ' ' << ans.y << ' ';

	// get angle to first colour
	auto angle = get_direction_angle(input.params, leftmost, colourcount[3], ans);

	// MISSING NEWLINE HERE; SHOULD BE REJECTED
	cout << angle;

	// cerr << "POSITION: " << ans.x << ' ' << ans.y << endl;
	// cerr << "ANGLE: " << angle << endl;
	return 0;
}
