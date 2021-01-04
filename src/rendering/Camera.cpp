
#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <QDebug>

using namespace ppvr::rendering;


Camera::Camera(float width, float height): width{width}, height{height} {
	this->update();
}

Camera::~Camera() {

}


void Camera::setViewportSize(float width, float height) {
	this->width = width;
	this->height = height;
	this->update();
}

void Camera::update() {
	aspectRatio = width / height;

	//for(size_t i = 0; i<4; i++) {
	//	glm::vec4 row = glm::row(openGLProj2VulkanProjMatrix, i);
	//	qDebug() << "row " << (i+0) << ": " << row.x << ", " << row.y << ", " << row.z << ", " << row.w;
	//}

	updateProjectionMatrix();
	updateViewMatrix();

	//_VPmatrix.set(_ProjMatrix).mul(_ViewMatrix);
	// view_projection_ = clip * projection * view; // https://github.com/LunarG/VulkanSamples/commit/0dd36179880238014512c0637b0ba9f41febe803
	finalCameraData.vpMatrix = openGLProj2VulkanProjMatrix * openGlProjMatrix * finalCameraData.viewMatrix;
	//finalCameraData.vpMatrix = finalCameraData.viewMatrix;
	// _ViewMatrix.invert(_ViewInvMatrix);
	finalCameraData.viewInvMatrix = glm::inverse(finalCameraData.viewMatrix);

	if(useRotationMatrix) {
		viewDirection = glm::vec3(0.0, 0.0, -1.0) * glm::mat3x3(finalCameraData.viewMatrix);
	} else {
		// _ViewDirection.set(_Target).sub(_Pos).normalize();
		viewDirection = glm::normalize(target - pos);
	}
}


void Camera::updateProjectionMatrix() {
	if (this->orthogonal) {
		this->openGlProjMatrix = glm::ortho(left, right, bottom, top, near, far);
	}
	else {
		// Build the projection matrix. Watch out here for integer division
		// when computing the aspect ratio!
		this->openGlProjMatrix = glm::perspective(fieldOfViewRad, aspectRatio, near, far);
		//metalProjMatrix = openGLProj2MetalProjMatrix * openGlProjMatrix;
	}
}

void Camera::updateViewMatrix() {
	if(useRotationMatrix) {
		//finalCameraData.viewMatrix = cameraRotation;
		finalCameraData.viewMatrix = glm::translate(glm::mat4{1.0f}, glm::vec3(0.0f, 0.0f, -radius)) * cameraRotation;
	} else {
		pos.z = radius * glm::cos(azimuth) * glm::sin(polar);
		pos.x = radius * glm::sin(azimuth) * glm::sin(polar);
		pos.y = radius * glm::cos(polar);
		
		//qDebug() << "pos: " << pos.x << ", " << pos.y << ", " << pos.z;
		
		// Set lookat view matrix
		//finalCameraData.viewMatrix = float4x4.makeLookAt(pos.x, pos.y, pos.z,			// the position of your camera, in world space
		//							 target.x, target.y, target.z,	// where you want to look at, in world space
		//							 up.x, up.y, up.z				// probably glm::vec3(0,1,0), but (0,-1,0) would make you looking upside-down, which can be great too
		//)
		finalCameraData.viewMatrix = glm::lookAt(pos, target, up);
	}
}

void Camera::setPostion2TopRight() {
	radius = 2.2;
	azimuth = 0.36;
	polar = 1.09;
	update();
}

void Camera::zoom(float t) {
	// zoom by changing field of view
	/*
	fieldOfView = glm::max(20.0f, glm::min(mFieldOfView - t, 120.0f));
	buildProjectionMatrix();
	*/

	// zoom by changing position
	radius -= t;
	if(radius < 0.1) {
		radius = 0.1;
	}

	//Vector3f f = (new Vector3f(_Target)).sub(_Pos).normalize();
	//_Pos.add(f.mul(t));

	update();
}

void  Camera::rotateAzimuth(float t) {
	if(useRotationMatrix) {
		cameraRotation = glm::rotate(glm::mat4{1.0f}, t, glm::vec3{0.0f, 1.0f, 0.0f}) * cameraRotation;
	} else {
		azimuth += t;
	}
	update();
}


void Camera::rotatePolar(float t) {
	if(useRotationMatrix) {
		
		//double distance = this.getDistance();
		//this.viewMatrixPoint.multLeft (new CG1Matrix4x4().setTranslate(0, 0, distance));
		cameraRotation =  glm::rotate(glm::mat4{1.0f}, t, glm::vec3{1.0f, 0.0f, 0.0f}) * cameraRotation;
		//this.viewMatrixPoint.multLeft (new CG1Matrix4x4().setTranslate(0, 0, -distance));
		
	} else {
		polar += t;
		polar = glm::max(0.1f, polar);
		polar = glm::min((float)M_PI - 0.1f, polar);
	}
	update();
}


void Camera::rotateUp(float t)
{
	glm::vec3 f = glm::normalize(target - pos);
	glm::vec3 u = glm::normalize(up);
	glm::vec3 s = glm::normalize(glm::cross(f, u));
	glm::mat4 rotation = glm::rotate(glm::mat4(), t, s);
	glm::vec3 newF = glm::vec3(rotation*glm::vec4(f, 0));
	up = glm::vec3(rotation*glm::vec4(up, 0.0f));
	target = pos + newF;
	update();
}

void Camera::rotateDown(float t)
{
	glm::vec3 f = glm::normalize(target - pos);
	glm::vec3 u = glm::normalize(up);
	glm::vec3 s = glm::normalize(glm::cross(f, u));
	glm::mat4 rotation = glm::rotate(glm::mat4(), -t, s);
	glm::vec3 newF = glm::vec3(rotation*glm::vec4(f, 0.0f));
	up = glm::vec3(rotation*glm::vec4(up, 0.0f));
	target = pos + newF;
	update();
}

void Camera::rotateLeft(float t)
{
	glm::vec3 f = glm::normalize(target - pos);
	glm::vec3 u = glm::normalize(up);
	glm::mat4 rotation = glm::rotate(glm::mat4(), t, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 newF = glm::vec3(rotation*glm::vec4(f, 0.0f));
	target = pos + newF;
	up = glm::vec3(rotation*glm::vec4(up, 0.0f));
	update();
}

void Camera::rotateRight(float t)
{
	glm::vec3 f = glm::normalize(target - pos);
	glm::vec3 u = glm::normalize(up);
	glm::mat4 rotation = glm::rotate(glm::mat4(), -t, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 newF = glm::vec3(rotation*glm::vec4(f, 0.0f));
	target = pos + newF;
	up = glm::vec3(rotation*glm::vec4(up, 0.0f));
	update();
}

void Camera::moveForwards(float t) {
	glm::vec3 f = glm::normalize(target - pos);
	pos += f*t;
	target += f*t;
	update();
}

void Camera::moveBackwards(float t)
{
	glm::vec3 f = glm::normalize(target - pos);
	pos -= f*t;
	target -= f*t;
	update();
}

void Camera::moveLeft(float t)
{
	glm::vec3 f = glm::normalize(target - pos);
	glm::vec3 u = glm::normalize(up);
	glm::vec3 s = glm::normalize(glm::cross(f, u));
	pos -= s*t;
	target -= s*t;
	update();
}

void Camera::moveRight(float t)
{
	glm::vec3 f = glm::normalize(target - pos);
	glm::vec3 u = glm::normalize(up);
	glm::vec3 s = glm::normalize(glm::cross(f, u));
	pos += s*t;
	target += s*t;
	update();
}

void Camera::moveUp(float t)
{
	glm::vec3 f = glm::normalize(target - pos);
	glm::vec3 u = glm::normalize(up);
	glm::vec3 s = glm::normalize(glm::cross(f, u));
	u = glm::cross(s, f);
	pos += u*t;
	target += u*t;
	update();
}

void Camera::moveDown(float t)
{
	glm::vec3 f = glm::normalize(target - pos);
	glm::vec3 u = glm::normalize(up);
	glm::vec3 s = glm::normalize(glm::cross(f, u));
	u = glm::cross(s, f);
	pos -= u*t;
	target -= u*t;
	update();
}

// creates an origin and a direction for a given image pixel
void Camera::ray(int x, int y, glm::vec3& origin, glm::vec3& direction) const {
		/*
		Matrix44f cameraToWorld;
		Vec3f *framebuffer = new Vec3f[options.width * options.height];
		Vec3f *pix = framebuffer;
		float scale = tan(deg2rad(options.fov * 0.5));
		float imageAspectRatio = options.width / (float)options.height;
		Vec3f orig;
		cameraToWorld.multVecMatrix(Vec3f(0), orig);
		for (uint32_t j = 0; j < options.height; ++j) {
			for (uint32_t i = 0; i < options.width; ++i) {
				float x = (2 * (i + 0.5) / (float)options.width - 1) * imageAspectRatio * scale;
				float y = (1 - 2 * (j + 0.5) / (float)options.height) * scale;
				Vec3f dir;
				cameraToWorld.multDirMatrix(Vec3f(x, y, -1), dir);
				dir.normalize();
				*(pix++) = castRay(orig, dir, objects, lights, options, 0);
			}
		}
		*/

		float scale = tan(fieldOfViewRad * 0.5);
		
		float screenDirX = (		((2.0 * ((float)x + 0.5)) / width ) - 1.0	);
		float screenDirY = (1.0 - 	((2.0 * ((float)y + 0.5)) / height)		);
		direction = glm::vec3{screenDirX, screenDirY, -1};
		direction.x *= scale * aspectRatio;
		direction.y *= scale;
	
		//java: direction.mulDirection(finalCameraData.viewMatrix); // ignore matrix column 4 (tralsation)
		direction = glm::normalize( glm::mat3x3(finalCameraData.viewMatrix) * direction );
	
		//java: origin.set(0,0,0); origin.mulPosition(finalCameraData.viewMatrix); // add the 4th column of the matrix (translation) to the result vector (could be cached becaus it only depends on the camera position and is therefor independent from the screen pixel position)
		// add the 4th column of the matrix (translation) to the result vector (could be cached becaus it only depends on the camera position and is therefor independent from the screen pixel position)
		origin = glm::vec3{finalCameraData.viewInvMatrix[3]}; // get the first 3 rows (glm::vec3{...}) of the last column ([3]). This should be the translation part of the matrix and therefore representing the camera postion postion.
	
	}

