/*********************************************************************
 *  Author  : Himangshu Saikia
 *  Init    : Tuesday, October 17, 2017 - 10:24:30
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#include <labraytracer/triangle.h>
#include <labraytracer/util.h>
#include <memory>

namespace inviwo {

Triangle::Triangle() {
}

Triangle::Triangle(const vec3& v0, const vec3& v1, const vec3& v2, const vec3& uvw0,
                   const vec3& uvw1, const vec3& uvw2) {
    mVertices[0] = v0;
    mVertices[1] = v1;
    mVertices[2] = v2;
    mUVW[0] = uvw0;
    mUVW[1] = uvw1;
    mUVW[2] = uvw2;
}

bool Triangle::closestIntersection(const Ray& ray, double maxLambda,
                                   RayIntersection& intersection) const {
    //Programming TASK 1: Implement this method
    //Your code should compute the intersection between a ray and a triangle.
    //
    //If you detect an intersection, the return type should look similar to this:
    //if(rayIntersectsTriangle)
    //{
    //  intersection = RayIntersection(ray,shared_from_this(),lambda,ray.normal,uvw);
    //  return true;
    //} 
    //
    // Hints :
    // Ray origin p_r : ray.getOrigin()
    // Ray direction t_r : ray.getDirection()
    // Compute the intersection point using ray.pointOnRay(lambda) 

	vec3 t1 = mVertices[1] - mVertices[0];
	vec3 t2 = mVertices[2] - mVertices[0];
	vec3 normal = cross(t1, t2);

	double d = dot(ray.getDirection(), normal);
	if (fabs(d) < Util::epsilon) return false;

	double a = dot((mVertices[0] - ray.getOrigin()), normal);
	double lambda = a / d;
	if (lambda < 0 || lambda + Util::epsilon > maxLambda) return false;

	vec3 P_0 = ray.pointOnRay(lambda);

	// inside outside test
	vec3 edge0 = mVertices[1] - mVertices[0];
	vec3 edge1 = mVertices[2] - mVertices[1];
	vec3 edge2 = mVertices[0] - mVertices[2];
	vec3 intersectionV0 = P_0 - mVertices[0];
	vec3 intersectionV1 = P_0 - mVertices[1];
	vec3 intersectionV2 = P_0 - mVertices[2];

	vec3 C = cross(edge0, intersectionV0);
	if (dot(normal, C) < 0) return false;
	
	C = cross(edge1, intersectionV1);
	if (dot(normal, C) < 0) return false;

	C = cross(edge2, intersectionV2);
	if (dot(normal, C) < 0) return false;

	// get intersection point if point is within triangle
	const vec3 uvw(0, 0, 0);
	intersection = RayIntersection(ray,shared_from_this(),lambda,normal,uvw);
	return true;
}

bool Triangle::anyIntersection(const Ray& ray, double maxLambda) const {
    RayIntersection temp;
    return closestIntersection(ray, maxLambda, temp);
}

void Triangle::drawGeometry(std::shared_ptr<BasicMesh> mesh,
                            std::vector<BasicMesh::Vertex>& vertices) const {
    auto indexBuffer = mesh->addIndexBuffer(DrawType::Lines, ConnectivityType::None);

    Util::drawLineSegment(mVertices[0], mVertices[1], vec4(0.2, 0.2, 0.2, 1), indexBuffer,
                          vertices);
    Util::drawLineSegment(mVertices[1], mVertices[2], vec4(0.2, 0.2, 0.2, 1), indexBuffer,
                          vertices);
    Util::drawLineSegment(mVertices[2], mVertices[0], vec4(0.2, 0.2, 0.2, 1), indexBuffer,
                          vertices);
}

} // namespace
