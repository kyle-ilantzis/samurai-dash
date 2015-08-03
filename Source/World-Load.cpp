// Other
#include "World.h"
#include "ParsingHelper.h"
#include "RealTimeCollisionDetection.h"
#include "Animation.h"
#include "SplineFactory.h"
// Models
#include "WolfModel.h"
#include "CubeModel.h"
#include "SphereModel.h"
#include "PlayerModel.h"
#include "UFOModel.h"
#include "CapsuleModel.h"
#include "SkyboxModel.h"
#include "Obstacles.h"
#include "Discoball.h"


using namespace std;
using namespace glm;
using namespace rtcd;

const char* World::sceneFile = "../Assets/Scenes/SamuraiDash.scene";

void World::LoadScene() {

	// The world's scene for samurai-dash
	// Do any complex dynamic initialization in here

	mSplineModel = SplineFactory::LoadSpline();
	//mModel.push_back(mSplineModel);


	// Creating the Models
	mPlayerModel = new PlayerModel();
	mWolfModel = new WolfModel();
	mUFOModel = new UFOModel();

	// Create the capsue for sheep
	Capsule* sheepCapsule = new Capsule();
	sheepCapsule->a = vec3(0, 0.25, 0);;
	sheepCapsule->b = vec3(0, 0.5, 0);
	sheepCapsule->r = 0.68;
	mPlayerModel->setCapsuleBoundingVolume(sheepCapsule);

	// Poop particle system for sheep
	ci_string str = "particleSystem = \"poop\"\n";
	ci_istringstream iss(str);
	mPlayerModel->Load(iss);

	// Pushing Models To the World.
	mModel.push_back(mUFOModel);
	mModel.push_back(mPlayerModel);
	mModel.push_back(mWolfModel);


	// The wolf follows ths Sheep Player.
	mWolfModel->SetParent(mPlayerModel);
	
	// Create the obstacles
	mObstacles->PopulateRandomSample();

	// Finally the static samurai-dash scene is loaded
	LoadScene(sceneFile);

	// Movement for Models
	mWolfModel->setAnimation(FindAnimation("\"BackAndForth\""));

	// Create skybox and push to scene
	SkyboxModel* skybox = new SkyboxModel();
	mModel.push_back(skybox);
}

void World::LoadScene(const char * scene_path)
{
	// Using case-insensitive strings and streams for easier parsing
	ci_ifstream input;
	input.open(scene_path, ios::in);

	// Invalid file
	if (input.fail())
	{
		fprintf(stderr, "Error loading file: %s\n", scene_path);
		getchar();
		exit(-1);
	}

	ci_string item;
	while (std::getline(input, item, '['))
	{
		ci_istringstream iss(item);

		ci_string result;
		if (std::getline(iss, result, ']'))
		{
			if (result == "player")
			{
				// Box attributes
				PlayerModel* player = new PlayerModel();
				player->Load(iss);
				mModel.push_back(player);

				mPlayerModel = player;
			}
			else if (result == "wolf")
			{
				// Box attributes
				WolfModel* wolf = new WolfModel();
				wolf->Load(iss);
				mModel.push_back(wolf);
			}
			else if (result == "ufo")
			{
				UFOModel* ufo = new UFOModel();
				ufo->Load(iss);
				mModel.push_back(ufo);
			}
			else if (result == "cube")
			{
				// Box attributes
				CubeModel* cube = new CubeModel();
				cube->Load(iss);
				mModel.push_back(cube);
			}
			else if (result == "sphere")
			{
				SphereModel* sphere = new SphereModel();
				sphere->Load(iss);
				mModel.push_back(sphere);
			}
			else if (result == "animationkey")
			{
				AnimationKey* key = new AnimationKey();
				key->Load(iss);
				mAnimationKey.push_back(key);
			}
			else if (result == "animation")
			{
				Animation* anim = new Animation();
				anim->Load(iss);
				mAnimation.push_back(anim);
			}
			else if (result.empty() == false && result[0] == '#')
			{
				// this is a comment line
			}
			else
			{
				fprintf(stderr, "Error loading scene file... !");
				getchar();
				exit(-1);
			}
		}
	}
	input.close();

	// Set Animation vertex buffers
	for (vector<Animation*>::iterator it = mAnimation.begin(); it < mAnimation.end(); ++it)
	{
		// Draw model
		(*it)->CreateVertexBuffer();
	}
}