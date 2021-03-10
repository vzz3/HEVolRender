#pragma once

#ifdef _WIN32
	#define _USE_MATH_DEFINES
	#include <cmath>
	#define M_PI 3.14159265359
#endif

#include <vulkan/vulkan.h>
#include <QVulkanDeviceFunctions>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/trigonometric.hpp> // glm::vec4
#include "uniform/CameraUniformBufferObject.hpp"

using ppvr::rendering::uniform::CameraUniformBufferObject;

namespace ppvr {
	namespace rendering {
		class Camera {
		public:
		
			Camera(float width, float height);
			~Camera();
			
			void setViewportSize(float width, float height);
	
			float getWidth() const {
				return this->width;
			}
	
	 		float getHeight() const {
				return this->height;
			}
	
		 	const glm::mat4 & getVPmatrix() const {
				return this->finalCameraData.vpMatrix;
			}
	
			const glm::vec3 & getViewDirection() const {
				return this->viewDirection;
			}
			
			float getRadius() const {
				return radius;
			}
			
			const CameraUniformBufferObject & getFinalData() const {
				return finalCameraData;
			}
	
		private:
			void update();
	
	 		void updateProjectionMatrix();
	
			void updateViewMatrix();
	
	
		public:
			void setPostion2TopRight();
	
	 		void zoom(float t);

			/**
			 * rotateY
			 * around y axis (use for mouse x move)
			 *
			 * @param t
			 */
			void  rotateAzimuth(float t);

			/**
			 * rotateX
			 * around x axis (use for mouse y move)
			 *
			 * @param t
			 */
			void rotatePolar(float t);
			
		private: // private because this functions are not tested
			void rotateUp(float t);
			void rotateDown(float t);
			void rotateLeft(float t);
			void rotateRight(float t);
	
		private: // private because this functions are not tested
			void moveLeft(float t);
			void moveRight(float t);
			void moveForwards(float t);
			void moveBackwards(float t);
			void moveUp(float t);
			void moveDown(float t);
	
		public:
			void ray(int x, int y, glm::vec3& origin, glm::vec3& direction) const;
			
		private:
			float aspectRatio = 1.0f;
			float fieldOfViewDeg = 40.0f;
			float fieldOfViewRad = glm::radians(fieldOfViewDeg); // Converts degrees to radians and returns the result.
		
			float width;
			float height;
			
			float radius = 1.0f;
			float azimuth = 0.0f;
			float polar = M_PI / 2.0f;
			
			glm::vec3 pos{0.0f, 0.0f, -10.0f};
			glm::vec3 up{0.0f, 1.0f, 0.0f};
			glm::vec3 target{0.0f, 0.0f, 0.0f};
			
			float near = 0.01f;
			float far = 100.0f;
			// for orthogonal projection:
			float left = -100.0f;
			float right = 100.0f;
			float top = 100.0f;
			float bottom = -100.0f;
			
			
			bool orthogonal = false;
			
			// --- projection Matrix ---
			// projection matrix for openGL NDC (view frustum from (-1,-1,-1) to (1,1,1) with center (0,0,0) and therfore an size of (2,2,2))
			glm::mat4x4 openGlProjMatrix;
			// projection matrix for Metal NDC (view frustum from (-1,-1,0) to (1,1,1) with center (0,0,0.5) and therfore an size of (2,2,1))
			//glm::mat4x4 metalProjMatrix;
			
			// projection matrix for Vulkan NDC (view frustum from (-1,-1,0) to (1,1,1) with center (0,0,0.5) and therfore an size of (2,2,1) and a fliped y axis) https://matthewwellings.com/blog/the-new-vulkan-coordinate-system/
			glm::mat4x4 vulkanProjMatrix;
			
			const glm::mat4x4 openGLProj2MetalProjMatrix =  glm::transpose(glm::mat4x4({ // I write in row major but glm/glsl uses column major
				 1.0f,	 0.0f,	 0.0f,	 0.0f, // row 0
				 0.0f,	 1.0f,	 0.0f,	 0.0f, // row 1
				 0.0f,	 0.0f,	 0.5f,	 0.5f, // row 2
				 0.0f,	 0.0f,	 0.0f,	 1.0f  // row 3
			}));
			
			const glm::mat4x4 openGLProj2VulkanProjMatrix = glm::transpose(glm::mat4x4({ // I write in row major but glm/glsl uses column major
				 1.0f,	 0.0f,	 0.0f,	 0.0f, // row 0
				 0.0f,	-1.0f,	 0.0f,	 0.0f, // row 1
				 0.0f,	 0.0f,	 0.5f,	 0.5f, // row 2
				 0.0f,	 0.0f,	 0.0f,	 1.0f  // row 3
			}));
			
			const bool useRotationMatrix = false;
			glm::mat4x4 cameraRotation{1.0f}; // init identity matrix
			
		//	private var viewMatrix: float4x4! // worldToCamera
		//	private var viewInvMatrix: float4x4! // cameraToWorld
		//	private var vpMatrix: float4x4!
			CameraUniformBufferObject finalCameraData{};
			
			glm::vec3 viewDirection;
		};
	}
}
