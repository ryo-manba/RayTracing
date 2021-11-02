#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

color ray_color(const ray& r) {
	// unit_vectorで方位ベクトルが求まる
	vec3 unit_direction = unit_vector(r.direction());// r/r.length(sqrt(rx*rx, ry*ry, rz*rz))
	auto t = 0.5 * (unit_direction.y() + 1.0); // 0.5*(高さ+1.0) ->上が1,下が0
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0); // 白と水色のグラデーション
	// (1.0 -t) 上が0,下が1に変化
	// 1.0-t と t が重み
	// 上に行くにつれて t が大きくなる
	// 最初はtが大きいが徐々に小さくなる
}

int main()
{
	// Image
	const auto aspect_ratio = 16.0 / 9.0; // 画面比率
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	// Camera
	auto viewport_height = 2.0; // スクリーンの縦
	auto viewport_width = aspect_ratio * viewport_height; // 16.0/9.0*2.0 = 3.5555555555555554
	auto focal_length = 1.0; // 焦点距離

	auto origin = point3(0, 0, 0); // 視点
	auto horizontal = vec3(viewport_width, 0, 0); // 水平, x軸がviewport_width
	auto vertical = vec3(0, viewport_height, 0); // 垂直, y軸がviewport_height
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length); // z軸が焦点距離

	// Render
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; j--) {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; i++) {
			auto u = double(i) / (image_width - 1); // 見ている点の左からの距離
			auto v = double(j) / (image_height - 1); // 見ている点の下からの距離
			ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin); // 変化の大きさを求めるためにoriginを引いてる
			color pixel_color = ray_color(r);
			write_color(std::cout, pixel_color);
		}
	}

	std::cerr << "\nDone.\n";
}
