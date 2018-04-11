/*********************************************************************
 *  Author  : Himangshu Saikia
 *  Init    : Tuesday, October 17, 2017 - 10:24:56
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#include <labraytracer/sphere.h>
#include <labraytracer/util.h>

namespace inviwo {

Sphere::Sphere(const vec3& center, const double& radius) {
    center_ = center;
    radius_ = radius;
}

bool Sphere::closestIntersection(const Ray& ray, double maxLambda,
                                 RayIntersection& intersection) const {
    //Programming TASK 1: implement this method
    //Your code should compute the intersection between a ray and a sphere;

    //If you detect an intersection, the return type should look similar to this:
    //if(rayIntersectsSphere)
    //{
    //  intersection = RayIntersection(ray,shared_from_this(),lambda,ray.pointOnRay(lambda),uvw);
    //  return true;
    //}
    //()
    // Ray direction t_r : ray.getDir
    // Hints :
    // Ray origin p_r : ray.getOrigin
    // Compute the intersection point using ray.pointOnRay(lambda)

	vec3 rayToCenter = ray.getOrigin() - center_;
	double a = dot(ray.getDirection(), ray.getDirection());
	double b = 2 * dot(ray.getDirection(), rayToCenter);
	double c = dot(rayToCenter, rayToCenter) - pow(radius_, 2);

	double delta = pow(b, 2) - 4*a*c;
	if (delta < 0) return false;

	double lambda1 = (-b - sqrt(delta)) / (2 * a);
	double lambda2 = (-b + sqrt(delta)) / (2 * a);

	//double lambda;
	//if (lambda2 < 0 || lambda2 + Util::epsilon > maxLambda) {
	//	return false;
	//}
	//else lambda = lambda2;

	//if (lambda1 < 0 || lambda1 + Util::epsilon > maxLambda) {
	//	return false;
	//}
	//else lambda = lambda1;

	if (lambda1 > lambda2) std::swap(lambda1, lambda2);

	double lambda = lambda1;
	if (lambda1 < 0 || lambda1 + Util::epsilon > maxLambda) {
		lambda = lambda2;
		if (lambda2 < 0 || lambda2 + Util::epsilon > maxLambda) return false;
	}

	vec3 normal = Util::normalize(ray.pointOnRay(lambda) - center_);
	const vec3 uvw(0, 0, 0);
	intersection = RayIntersection(ray,shared_from_this(),lambda,normal,uvw);
	return true;
}

bool Sphere::anyIntersection(const Ray& ray, double maxLambda) const {
    RayIntersection temp;
    return closestIntersection(ray, maxLambda, temp);
}

void Sphere::drawGeometry(std::shared_ptr<BasicMesh> mesh,
                          std::vector<BasicMesh::Vertex>& vertices) const {
    auto indexBuffer = mesh->addIndexBuffer(DrawType::Lines, ConnectivityType::None);

    int lat = 8;
    int lon = 10;

    for (int i = 0; i < lat - 1; i++) {
        float theta1 = float(i * M_PI) / (lat - 1);
        float theta2 = float((i + 1) * M_PI) / (lat - 1);

        for (int j = 0; j < lon - 1; j++) {
            float phi1 = float(j * 2 * M_PI) / (lon - 1);
            float phi2 = float((j + 1) * 2 * M_PI) / (lon - 1);

            vec3 v1 = vec3(radius_ * sin(theta1) * cos(phi1), radius_ * sin(theta1) * sin(phi1),
                           radius_ * cos(theta1)) + center_;
            vec3 v2 = vec3(radius_ * sin(theta2) * cos(phi1), radius_ * sin(theta2) * sin(phi1),
                           radius_ * cos(theta2)) + center_;
            vec3 v3 = vec3(radius_ * sin(theta2) * cos(phi2), radius_ * sin(theta2) * sin(phi2),
                           radius_ * cos(theta2)) + center_;

            Util::drawLineSegment(v1, v2, vec4(0.2, 0.2, 0.2, 1), indexBuffer, vertices);
            Util::drawLineSegment(v2, v3, vec4(0.2, 0.2, 0.2, 1), indexBuffer, vertices);
        }
    }
}

} // namespace
