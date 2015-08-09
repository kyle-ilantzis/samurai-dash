#include "Billboard.h"
#include "Renderer.h"
#include "World.h"
#include "Camera.h"
#include <GL/glew.h>
#include "TopGun.h"

TopGun::TopGun()
{
	// Add Different Textures
	int billboardTextureID2 = TextureLoader::LoadTexture("../Assets/Textures/Goose.jpg");
	int billboardTextureID3 = TextureLoader::LoadTexture("../Assets/Textures/Iceman.jpg");
	int billboardTextureID4 = TextureLoader::LoadTexture("../Assets/Textures/Maverick.jpg");
	int billboardTextureID5 = TextureLoader::LoadTexture("../Assets/Textures/Top_Gun_Ending.jpg");
	int billboardTextureID6 = TextureLoader::LoadTexture("../Assets/Textures/TopGun.jpg");


	assert(billboardTextureID2 != 0);
	assert(billboardTextureID3 != 0);
	assert(billboardTextureID4 != 0);
	assert(billboardTextureID5 != 0);
	assert(billboardTextureID6 != 0);

	// Create New BillboardLists for them
	mpBillboardList2 = new BillboardList(10, billboardTextureID2);
	mpBillboardList3 = new BillboardList(10, billboardTextureID3);
	mpBillboardList4 = new BillboardList(10, billboardTextureID4);
	mpBillboardList5 = new BillboardList(10, billboardTextureID5);
	mpBillboardList6 = new BillboardList(10, billboardTextureID6);


	// Testing different billboards
	Billboard* b = new Billboard();
	b->size = glm::vec2(20.0, 10.0);
	b->position = glm::vec3(35.0, 5.0, -5.0);
	b->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	Billboard* b2 = new Billboard();
	b2->size = glm::vec2(20.0, 10.0);
	b2->position = glm::vec3(-35.0, 5.0, -5.0);
	b2->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	Billboard* b3 = new Billboard();
	b3->size = glm::vec2(20.0, 10.0);
	b3->position = glm::vec3(35.0, 5.0, -30.0);
	b3->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	mpBillboardList2->AddBillboard(b);
	mpBillboardList3->AddBillboard(b2);
	mpBillboardList4->AddBillboard(b3);
	mpBillboardList5->AddBillboard();
	mpBillboardList6->AddBillboard();
}

void TopGun::Update(float dt)
{
	mpBillboardList2->Update(dt);
	mpBillboardList3->Update(dt);
	mpBillboardList4->Update(dt);
	mpBillboardList5->Update(dt);
	mpBillboardList6->Update(dt);
}

void TopGun::Draw()
{
	mpBillboardList2->Draw();
	mpBillboardList3->Draw();
	mpBillboardList4->Draw();
	mpBillboardList5->Draw();
	mpBillboardList6->Draw();
}