#include "Discoball.h"

#include "EventManager.h"

using namespace glm;

Discoball::Discoball(vec3 size) : SphereModel(size, GL_TRIANGLES, &forEachVertex)
{
	SetScaling(glm::vec3(2.0f, 2.0f, 2.0f));
}

Discoball::~Discoball() {}

void Discoball::forEachVertex(SphereModel::Vertex* vertexBuffer, int len) {

	for (int i = 0; i < len; i += 3) {

		//bool show = (i % 2) == 0 || true;
		bool show = true;

		for (int j = i; j < i+3 && j < len; j++) {

			float rcx = EventManager::GetRandomFloat(0, 1);
			float rcy = EventManager::GetRandomFloat(0, 1);
			float rcz = EventManager::GetRandomFloat(0, 1);

			float rpx = EventManager::GetRandomFloat(0, 0.25);
			float rpy = EventManager::GetRandomFloat(0, 0.25);
			float rpz = EventManager::GetRandomFloat(0, 0.25);


			if (show) {
				vertexBuffer[j].position += vec3(rpx, rpy, rpz);
			}
			else {
				vertexBuffer[j].position = vec3(0);
			}

			vertexBuffer[j].color = vec3(rcx, rcy, rcz);
		}
	}
}