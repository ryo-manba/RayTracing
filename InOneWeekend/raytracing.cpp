#include <iostream>

int main()
{
	// Image
	const int image_width = 256;
	const int image_height = 256;

	// Render
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; j--) {
		std::cerr << "\rScanlines remaingin: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; i++) {
			auto r = double(i) / (image_width - 1); // i=255の時, r=255
			auto g = double(j) /(image_height - 1); // j=255の時, g=255
			auto b = 0.25;

			// 0〜255の範囲に変換する
			int ir = static_cast<int>(255.999 * r); // ()内部の値を明示的にint型にキャストしている(なくても同じ結果になる)
			int ig = static_cast<int>(255.999 * g);
			int ib = static_cast<int>(255.999 * b);

			std::cout << ir << ' ' << ig << ' ' << ib << '\n';
		}
	}
	std::cerr << "\nDone.\n";
}
