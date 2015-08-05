// Other
#include "World.h"
#include "ParsingHelper.h"
#include "RealTimeCollisionDetection.h"
#include "Animation.h"
#include "SplineFactory.h"

// Models
#include "BunnyModel.h"
#include "WolfModel.h"
#include "CubeModel.h"
#include "SphereModel.h"
#include "PlayerModel.h"
#include "CapsuleModel.h"
#include "SkyboxModel.h"
#include "Obstacles.h"
#include "Discoball.h"
#include "UFOModel.h"

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
	mBunnyModel = new BunnyModel();
	mBunnyModelTwo = new BunnyModel();
	mUFOModel = new UFOModel();

	// Create the capsue for Player Jet
	Capsule* JetCapsule = new Capsule();
	JetCapsule->a = vec3(210, 0, 0);;
	JetCapsule->b = vec3(-130, 0, 0);
	JetCapsule->r = 450;
	mPlayerModel->setCapsuleBoundingVolume(JetCapsule);

	// Jet Stream Particle System for Player Jet (Two Of Them)
	ci_string JetFlame = "particleSystem = \"JetFlame\"\n";
	ci_istringstream iss(JetFlame);
	mPlayerModel->Load(iss);
	ci_string JetFlame2 = "particleSystem = \"JetFlame2\"\n";
	ci_istringstream iss2(JetFlame2);
	mPlayerModel->Load(iss2);

	// Beam Particle System For UFO
	ci_string beamString = "particleSystem = \"UFOBeam\"\n";
	ci_istringstream isses(beamString);
	mUFOModel->Load(isses);

	// Pushing Models To the World.
	mModel.push_back(mPlayerModel);
	mModel.push_back(mWolfModel);
	mModel.push_back(mBunnyModel);
	mModel.push_back(mBunnyModelTwo);
	mModel.push_back(mUFOModel);

	// The wolf follows ths Player Model.
	mWolfModel->SetParent(mPlayerModel);
	mUFOModel->SetParent(mPlayerModel);
	
	// Create the obstacles
	mObstacles->PopulateRandomSample();

	// Finally the static samurai-dash scene is loaded
	LoadScene(sceneFile);

	// Movement for Models
	mWolfModel->setAnimation(FindAnimation("\"BackAndForth\""));
	mBunnyModel->setAnimation(FindAnimation("\"BunnyStanding\""));
	mBunnyModelTwo->setAnimation(FindAnimation("\"BunnyStanding2\""));
	mUFOModel->setAnimation(FindAnimation("\"UFOMove\""));

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
			else if (result == "bunnny")
			{
				// Box attributes
				BunnyModel* bunny = new BunnyModel();
				bunny->Load(iss);
				mModel.push_back(bunny);
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