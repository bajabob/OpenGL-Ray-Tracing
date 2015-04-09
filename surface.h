
#ifndef RENDERABLE
#define RENDERABLE

#include <queue>
using std::priority_queue;
#include <vector>
using std::vector;
#include <cmath>
using std::pow;

#include <armadillo>
using arma::vec;
using arma::fvec;
using arma::norm;

class surface;

#include "ray.h"
#include "light.h"
#include "ray_intersection.h"

class surface
{
public:

	surface(const fvec &color,
			const fvec &specular,
			const double &specular_exponent,
			const double &reflect_intersections,
			const double &refract_intersections,
			const double &snell_coeffiecant):
				color(color),
				specular(specular),
				specular_exponent(specular_exponent),
				reflect_intersections(reflect_intersections),
				refract_intersections(refract_intersections),
				snell_coefficient(snell_coefficient)
	{}

	/**
	 * All objects to be rendered (planes, spheres, etc.) must
	 * 	implement this function to calculate it's intersection
	 * 	with some casted ray
	 */
    virtual ray_intersection cast_ray(const ray &r) const = 0;

    fvec get_color() const{
    	return this->color;
    }

    fvec get_specular() const{
    	return this->specular;
    }

    double get_specular_exponent() const{
    	return this->specular_exponent;
    }

private:

    fvec color;
    fvec specular;

    double specular_exponent;
    double reflect_intersections;
    double refract_intersections;
    double snell_coefficient;

};

#endif