#include "World.h"
#include "ParsingHelper.h"

#include "WolfModel.h"
#include "CubeModel.h"
#include "SphereModel.h"
#include "PlayerModel.h"
#include "Animation.h"
#include "SplineFactory.h"
#include "SkyboxModel.h"
#include "CapsuleModel.h"

#include "RealTimeCollisionDetection.h"

using namespace std;
using namespace glm;
using namespace rtcd;

const char* World::sceneFile = "../Assets/Scenes/SamuraiDash.scene";

void World::LoadScene() {

	// The world's scene for samurai-dash
	// Do any complex dynamic initialization in here

	mSplineModel = SplineFactory::LoadSpline();
	mModel.push_back(mSplineModel);


	mPlayerModel = new PlayerModel();
	ci_string str = "particleSystem = \"poop\"\n";
	ci_istringstream iss(str);
	mPlayerModel->Load(iss);

	mModel.push_back(mPlayerModel);

	// Finally the static samurai-dash scene is loaded
	LoadScene(sceneFile);

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
			if (result == "player") // FIXME - temporary collision test setup
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