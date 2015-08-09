#include "Billboard.h"
#include "Renderer.h"
#include "World.h"
#include "Camera.h"
#include <GL/glew.h>
#include "TopGun.h"

TopGun::TopGun()
{
	// Add Different Textures
	int billboardTextureID2 = TextureLoader::LoadTexture("../Assets/Textures/BillboardTest.bmp");
	int billboardTextureID3 = TextureLoader::LoadTexture("../Assets/Textures/BillboardTest.bmp");
	int billboardTextureID4 = TextureLoader::LoadTexture("../Assets/Textures/BillboardTest.bmp");

	assert(billboardTextureID2 != 0);
	assert(billboardTextureID3 != 0);
	assert(billboardTextureID4 != 0);

	// Create New BillboardLists for them
	mpBillboardList2 = new BillboardList(2048, billboardTextureID2);
	mpBillboardList3 = new BillboardList(2048, billboardTextureID3);
	mpBillboardList4 = new BillboardList(2048, billboardTextureID4);

	// Testing different billboards

	Billboard* b = new Billboard();
	b->size = glm::vec2(50.0, 50.0);
	b->position = glm::vec3(15.0, 5.0, -5.0);
	b->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	Billboard* b2 = new Billboard();
	b2->size = glm::vec2(50.0, 50.0);
	b2->position = glm::vec3(-15.0, 5.0, -5.0);
	b2->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	Billboard* b3 = new Billboard();
	b->size = glm::vec2(50.0, 50.0);
	b->position = glm::vec3(15.0, 5.0, -15.0);
	b->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	mpBillboardList2->AddBillboard(b);
	mpBillboardList3->AddBillboard(b2);
	mpBillboardList4->AddBillboard(b3);
}

void TopGun::Update(float dt)
{
	mpBillboardList2->Update(dt);
	mpBillboardList3->Update(dt);
	mpBillboardList4->Update(dt);
}

void TopGun::Draw()
{
	mpBillboardList2->Draw();
	mpBillboardList3->Draw();
	mpBillboardList4->Draw();
}