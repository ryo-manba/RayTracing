#include "rtweekend.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

#include <iostream>
/*
double hit_sphere(const point3& center, double radius, const ray& r) {
	vec3 oc = r.origin() - center; // 視点 - (0,0,-1) スクリーンの真ん中から視点に向かうベクトル
	auto a = r.direction().length_squared();
	auto half_b = dot(oc, r.direction());
	auto c = oc.length_squared()- radius * radius;
	auto discriminant = half_b * half_b - a * c; // 解の公式のルートの中身
	if (discriminant < 0) // 球に触れてないとき
		return -1.0;
	else
		return (-half_b - sqrt(discriminant)) / a; // 解の公式で求めた t の値 (-でtが小さい方)
}

color ray_color(const ray& r) {
	auto t = hit_sphere(point3(0, 0, -1), 0.5, r);
	if (t > 0.0)
	{
		vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1)); // at=origin + t*direction
		return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1); // スクリーン中心からレイと球の交点
	}
	// unit_vectorで方位ベクトルが求まる
	vec3 unit_direction = unit_vector(r.direction());// r/r.length(sqrt(rx*rx, ry*ry, rz*rz))
	t = 0.5 * (unit_direction.y() + 1.0); // 0.5*(高さ+1.0) ->上が1,下が0
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0); // 白と水色のグラデーション
	// (1.0 -t) 上が0,下が1に変化
	// 1.0-t と t が重み
	// 上に行くにつれて t が大きくなる
	// 最初はtが大きいが徐々に小さくなる
}
*/

color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0,0,0);

	// 0ではなく、0.001にするのはにするのはシャドウアクネ対策
    if (world.hit(r, 0.001, infinity, rec)) {
        point3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth-1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}


int main()
{
	// Image
	const auto aspect_ratio = 16.0 / 9.0; // 画面比率
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 100;
	const int max_depth = 50;

	// World
	hittable_list world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

	// Camera
	camera cam;

	// Render
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; j--) {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; i++) {
			color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; s++) {
				auto u = (i + random_double()) / (image_width - 1); // 見ている点の左からの距離
				auto v = (j + random_double()) / (image_height - 1); // 見ている点の下からの距離
				ray r = cam.get_ray(u, v); // 変化の大きさを求めるためにoriginを引いてる
				pixel_color += ray_color(r, world, max_depth);
			}
			write_color(std::cout, pixel_color, samples_per_pixel);
		}
	}

	std::cerr << "\nDone.\n";
}
