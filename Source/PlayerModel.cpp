#include "AssetsDir.h"

#include "PlayerModel.h"

#include "EventManager.h"
#include "World.h"
#include "SplineFactory.h"

#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/gtx/quaternion.hpp>

using namespace std;
using namespace glm;

const float PlayerModel::DEFAULT_SPLINE_TIME_SPEED = 0.25f;
const float PlayerModel::DEFAULT_MOVE_SPEED = 7.0f;
const float PlayerModel::MODEL_SPACE_HEIGHT_OFFSET = 0.0f;

glm::vec3 a (0.0f, 0.0f, 0.0f );
glm::vec3 b (0.0f, 0.0f, 0.0f );
glm::vec3 c (0.686275f, 0.933333f, 0.933333f );
const glm::vec3 PlayerModel::SHEEP_SHAPE_COLORS[] = { a,b,c };

PlayerModel::PlayerModel() : 
	ObjectModel(HOLY_SHEEP, HOLY_SHEEP_MATERIAL, SHEEP_SHAPE_COLORS),
	mCurrentSplineTime(),
	mSplineTimeSpeed(DEFAULT_SPLINE_TIME_SPEED),
	mMoveSpeed(DEFAULT_MOVE_SPEED),
	mTrack(TRACK_MIDDLE),
	mTrackState(*this),
	mMoveState(*this),
	mPlayerState(&mTrackState) {

	SetScaling(vec3(3));
}

void PlayerModel::Update(float dt) {

	if (!World::GetInstance()->GetSpline()) { return;  }

	mPlayerState->Update(dt);
}	

void PlayerModel::UpdatePosition(float dt) {

	mCurrentSplineTime += mSplineTimeSpeed * dt;

	SplineModel::Plane p = World::GetInstance()->GetSpline()->PlaneAt(mCurrentSplineTime);
	float trackPieceWidth = SplineFactory::trackWidth / 3;

	SetPosition(p.position + vec3(0, PlayerModel::MODEL_SPACE_HEIGHT_OFFSET, 0) + TrackShiftDir(mTrack) * trackPieceWidth);

	vec3 j = vec3(0, 1, 0);
	vec3 B = normalize(cross(p.tangent, p.normal));

	bool uphill = dot(j, p.tangent) > 0;
	float rotation = degrees(acos(dot(B, j))) * (uphill ? -1 : 1);

	quat quat1 = angleAxis(180.0f, vec3(0,1,0));
	quat quat2 = angleAxis(rotation, p.normal);

	quat quatRotation = quat2 * quat1;

	SetRotation(axis(quatRotation), angle(quatRotation));
	
}

vec3 PlayerModel::TrackShiftDir(Track dir) {

	SplineModel::Plane p = World::GetInstance()->GetSpline()->PlaneAt(mCurrentSplineTime);

	vec3 trackShift = vec3(0);
	switch (dir) {
	case TRACK_MIDDLE:
		return vec3(0);
	case TRACK_LEFT:
		return p.normal;		
	case TRACK_RIGHT:
		return -p.normal;
	}
}

void TrackState::setup() {
	// Consume the first press when coming back from MoveState.
	// For some reason IsKeyPressed will return true when no key is pressed.
	// Need to RTFM.
	mFirstPress = true;
}

void TrackState::Update(float dt) {

	mPlayer.UpdatePosition(dt);

	bool leftPressed = EventManager::IsKeyPressed(GLFW_KEY_LEFT) && !mFirstPress;
	bool rightPressed = EventManager::IsKeyPressed(GLFW_KEY_RIGHT) && !mFirstPress;
	
	mFirstPress = false;

	bool left = leftPressed && mPlayer.mTrack != TRACK_LEFT;
	bool right = rightPressed && mPlayer.mTrack != TRACK_RIGHT;

	if (left) {
		mPlayer.mMoveState.SetTrackMove(TRACK_LEFT);
	}
	else if (right) {
		mPlayer.mMoveState.SetTrackMove(TRACK_RIGHT);
	}

	if (left || right) {
		mPlayer.mMoveState.setup();
		mPlayer.mPlayerState = &mPlayer.mMoveState;
	}
}

void MoveState::SetTrackMove(Track dir) {
	mDir = dir;
}

void MoveState::Update(float dt) {

	PlayerState::Update(dt);
	mPlayer.UpdatePosition(dt);

	float trackPieceWidth = SplineFactory::trackWidth / 3;
	vec3 trackShift = mPlayer.TrackShiftDir(mDir) * mPlayer.mMoveSpeed * mCurrentTime;

	mPlayer.SetPosition(mPlayer.GetPosition() + trackShift);

	if (length(trackShift) >= trackPieceWidth) {
		int next = (int)mPlayer.mTrack + (mDir == TRACK_LEFT ? -1 : 1);
		Track nextTrack = (Track)clamp(next, 0, 2);

		mPlayer.mTrack = nextTrack;

		mPlayer.mTrackState.setup();
		mPlayer.mPlayerState = &mPlayer.mTrackState;
	}
}
