/*********************************************************************
 *  Author  : Himangshu Saikia
 *  Init    : Tuesday, October 24, 2017 - 17:17:44
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#include <labraytracer/phongmaterial.h>
#include <labraytracer/util.h>

namespace inviwo {

PhongMaterial::PhongMaterial(const vec3& color, const double reflectance, const double shininess,
    const vec3& ambientMaterialColor, const vec3& diffuseMaterialColor, const vec3& specularMatierialColor) 
    : Material(color, reflectance) {

    constexpr double LightIntensity = 100.0;

    shininess_ = shininess;
    ambientMaterialColor_   = Util::scalarMult(LightIntensity, ambientMaterialColor);
    diffuseMaterialColor_   = Util::scalarMult(LightIntensity, diffuseMaterialColor);
    specularMatierialColor_ = Util::scalarMult(LightIntensity, specularMatierialColor);
}

vec4 PhongMaterial::shade(const RayIntersection& intersection, const Light& light) const {
    // get normal and light direction
    vec3 N = intersection.getNormal();
    vec3 L = Util::normalize(light.getPosition() - intersection.getPosition());

    double cosNL = std::max(double(dot(N, L)), double(0));

    // Programming Task 2: Extend this method.
    // This method currently implements a Lambert's material with ideal
    // diffuse reflection.
    // Your task is to implement a Phong shading model.
    //
    // Hints:
    //
    // 1. This function should return the sum of diffuse and specular parts (no ambient part)
    // 2. The used light color for each type (diffuse/specular) from the light source 
    //    is the light color divided by the quadratic distance of the light source from 
    //    the point of intersection. (quadratic falloff)
    // 3. The view vector V is the direction of the ray which intersects the object.
    // 4. The rest of the terms as per the slides are as follows
    // 5. You have to take into account shininess_ (p), material colors, light colors 
    //    light, view, reflection and normal vector.
    //    
    //

	// SPECULAR
	vec3 viewRay = -intersection.getRay().getDirection();
	vec3 nViewRay = Util::normalize(viewRay);
	vec3 reflectRay = Util::scalarMult(2 * cosNL, N) - L;
	vec3 nReflectRay = Util::normalize(reflectRay);

	double angle = dot(nReflectRay, nViewRay);
	if (angle < 0) angle = 0.0;
	double specCoefficient = pow(angle, shininess_);

	double quadDistance = pow(length(light.getPosition() - intersection.getPosition()), 2);
	// component-wise vector product
	vec3 mixSpecColor(0, 0, 0);
	mixSpecColor.x = (light.getSpecularColor().x/quadDistance) * specularMatierialColor_.x;
	mixSpecColor.y = (light.getSpecularColor().y/quadDistance) * specularMatierialColor_.y;
	mixSpecColor.z = (light.getSpecularColor().z/quadDistance) * specularMatierialColor_.z;
	vec3 specular = Util::scalarMult(specCoefficient, mixSpecColor);

	double foo1 = light.getSpecularColor().x;
	double foo2 = specularMatierialColor_.x;
	double foo3 = this->color().x;
	// DIFFUSE

	// component-wise vector product
	vec3 mixDiffuseColor(0, 0, 0);
	mixDiffuseColor.x = (light.getDiffuseColor().x/quadDistance) * diffuseMaterialColor_.x;
	mixDiffuseColor.y = (light.getDiffuseColor().y/quadDistance) * diffuseMaterialColor_.y;
	mixDiffuseColor.z = (light.getDiffuseColor().z/quadDistance) * diffuseMaterialColor_.z;
	vec3 diffuse = Util::scalarMult(cosNL, mixDiffuseColor);

	foo1 = light.getDiffuseColor().x;
	foo2 = diffuseMaterialColor_.x;

	vec3 baseLine = Util::scalarMult(cosNL, this->color());
	return vec4(diffuse+specular, 1.0);

    //return vec4(Util::scalarMult(cosNL, this->color()), 1.0);

}

} // namespace
