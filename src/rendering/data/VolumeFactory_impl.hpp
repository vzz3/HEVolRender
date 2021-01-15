
#include <cassert>

using ppvr::rendering::data::VolumeFactory;

/*
template <typename T>
VolumeFactory<T>::VolumeFactory()
	: mWidth(0), mHeight(0), mDepth(0) {
}


template <typename T>
VolumeFactory<T>::~VolumeFactory() {}
*/

void VolumeFactory::createVolume1(Volume<uint16_t>& yVolume, const size_t ySize) {
	uint16_t val;

	yVolume.resize(0, 0, 0); // delete all;
	yVolume.resize(ySize, ySize, ySize, uint16_t{0});
	{
		uint32_t c = ySize/2;
		glm::uvec3 center{c};
		uint32_t radius = ySize/2;
		val = std::numeric_limits<uint16_t>::max()/2;
		addSphere(yVolume, center, radius, val);
	}
	{
		uint32_t min = ySize/4;
		glm::uvec3 boxMin = glm::uvec3{min};
		uint32_t max = ySize/4*3;
		glm::uvec3 boxMax = glm::uvec3{max};
		val = std::numeric_limits<uint16_t>::max();
		addBox( yVolume, boxMin, boxMax, val );
	}
}


void VolumeFactory::createVolume2(Volume<uint16_t>& yVolume, const size_t ySize) {
	uint16_t val;

	yVolume.resize(0, 0, 0); // delete all;
	yVolume.resize(ySize, ySize, ySize, uint16_t{0});

	{
		uint16_t c = ySize/2;
		glm::uvec3 center{(uint16_t)(ySize/2)};
		uint16_t radius = ySize/2;
		val = std::numeric_limits<uint16_t>::max()/5; // 0.2
		addSphere(yVolume, center, radius, val);
	}

	{
		uint16_t min = ySize/4;
		glm::uvec3 boxMin = glm::uvec3{min};
		uint16_t max = ySize/4*3;
		glm::uvec3 boxMax = glm::uvec3{max};
		val = std::numeric_limits<uint16_t>::max() / 2;
		addBox( yVolume, boxMin, boxMax, val );
	}

	{
		uint32_t c = ySize/5 * 4;
		glm::uvec3 center{c};
		uint32_t radius = ySize/5;
		val = std::numeric_limits<uint16_t>::max() / 4 * 3; // 0.2
		addSphere(yVolume, center, radius, val);
	}

}

void VolumeFactory::createVolume3(Volume<uint16_t>& yVolume, const size_t ySize) {
	uint16_t val;

	yVolume.resize(0, 0, 0); // delete all;
	yVolume.resize(ySize, ySize, ySize, uint16_t{0});


	for ( size_t x = 0; x < ySize/10; x++) {
		float xNorm = (float)x * 10.0f / (float)ySize;
		float xNormInv = 1.0f - xNorm;
		
		// v = VolumeFactory.addSphere(volume: v, center: int3(Int32(size/2)), radius: Int(xNormInv * Float(size)/2.0), value: xNorm);
		{
			uint16_t min = (uint16_t)( (0.5f - xNormInv/2.0f) * (float)ySize );
			glm::uvec3 boxMin = glm::uvec3{min};
			uint16_t max = (uint16_t)( (0.5f + xNormInv/2.0f) * (float)ySize );
			glm::uvec3 boxMax = glm::uvec3{max};
			val = (uint16_t)(xNorm * (float)std::numeric_limits<uint16_t>::max());
			addBox( yVolume, boxMin, boxMax, val );
		}
	}
}

template <typename T>
void VolumeFactory::addBox(Volume<T>& yVolume, const glm::uvec3& yMin, const glm::uvec3& yMax, const T& yValue) {
	for(int x = yMin.x; x < yMax.x; x++) {
		for(int y = yMin.y; y < yMax.y; y++) {
			for(int z = yMin.z; z < yMax.z; z++) {
				yVolume.set(x, y, z, yValue);
			}
		}
	}
}

template <typename T>
void VolumeFactory::addEllipsoid(Volume<T>& yVolume,  const glm::uvec3& yCenter,  const glm::uvec3& yRadius, const T& yValue) {
	glm::uvec3 min = yCenter - yRadius;
	glm::uvec3 max = yCenter + yRadius;
	
	glm::vec3 radiusSquered = glm::vec3{
			std::pow((float)yRadius.x, 2.0),
			std::pow((float)yRadius.x, 2.0),
			std::pow((float)yRadius.x, 2.0)};
	
	glm::vec3 centerDistSquered{};
	
	for(int x = min.x; x < max.x; x++) {
		for(int y = min.y; y < max.y; y++) {
			for(int z = min.z; z < max.z; z++) {
				// https://math.stackexchange.com/questions/76457/check-if-a-point-is-within-an-ellipse/76463
				centerDistSquered.x = std::pow((float)x - yCenter.x, 2.0),
				centerDistSquered.y = std::pow((float)y - yCenter.y, 2.0),
				centerDistSquered.z = std::pow((float)z - yCenter.z, 2.0);
				centerDistSquered = centerDistSquered / radiusSquered;
				
				if(centerDistSquered.x + centerDistSquered.y + centerDistSquered.z <= 1.0) {
					yVolume.set(x, y, z, yValue);
				}
			}
		}
	}
}

template <typename T>
void VolumeFactory::addSphere(Volume<T>& yVolume, const glm::uvec3& yCenter, uint32_t yRadius, const T& yValue) {
	glm::uvec3 r{yRadius};
	
	addEllipsoid(yVolume, yCenter, r, yValue);
}
