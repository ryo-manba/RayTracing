#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
	public:
		ray() {}
		ray(const point3& origin, const vec3& direction)
			: orig(origin), dir(direction)
		{}

		point3 origin() const { return orig; } // 視点
		vec3 direction() const { return dir; } // 視点からの変化

		point3 at(double t) const {
			return orig + t*dir;
		}

	public:
		point3 orig;
		vec3 dir;
};

#endif
