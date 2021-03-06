#include "AssetsDir.h"

#include "PlayerModel.h"

#include "EventManager.h"
#include "World.h"
#include "SplineFactory.h"
#include <iostream>

#include <GLFW/glfw3.h>
#include <glm/gtx/quaternion.hpp>
#include "Obstacles.h"
using namespace std;
using namespace glm;

const float PlayerModel::DEFAULT_SPLINE_TIME_SPEED = 0.50f;
const float PlayerModel::DEFAULT_MOVE_SPEED = 13.0f;
const float PlayerModel::MODEL_SPACE_HEIGHT_OFFSET = 1.3f;
//const quat quatLeft = angleAxis(-35.0f, vec3(0, 0, -1));
//const quat quatRight = angleAxis(35.0f, vec3(0, 0, -1));

const glm::vec3 PlayerModel::JET_SHAPE_COLORS[] = { JET_COLOR, JET_COLOR2, JET_COLOR, JET_COLOR, JET_COLOR2, JET_COLOR2, JET_COLOR2, JET_COLOR2, JET_COLOR, JET_COLOR, JET_COLOR,
													  JET_COLOR, JET_COLOR2, JET_COLOR2, JET_COLOR2, JET_COLOR, JET_COLOR, JET_COLOR, JET_COLOR2, JET_COLOR2, JET_COLOR, JET_COLOR,
													  JET_COLOR2, JET_COLOR2, JET_COLOR2, JET_COLOR2, JET_COLOR2, JET_COLOR2, JET_COLOR2, JET_COLOR2, JET_COLOR2, JET_COLOR2, JET_COLOR2,
													  JET_COLOR2, JET_COLOR2, JET_COLOR2, JET_COLOR2, JET_COLOR2, JET_COLOR2, JET_COLOR2, JET_COLOR2, JET_COLOR2, JET_COLOR };

PlayerModel::PlayerModel() : 
ObjectModel(HOLY_JET, HOLY_JET_MATERIAL, JET_SHAPE_COLORS),
	mCurrentSplineTime(),
	mSplineTimeSpeed(DEFAULT_SPLINE_TIME_SPEED),
	mMoveSpeed(DEFAULT_MOVE_SPEED),
	mTrack(TRACK_MIDDLE),
	mTrackState(*this),
	mMoveState(*this),
	mDeadState(*this),
	mGoalState(*this),
	mPlayerState(&mTrackState) {

	SetScaling(vec3(0.005));

	Reset();
}

void PlayerModel::Reset() {

	mCurrentSplineTime = 0;
	mTrack = TRACK_MIDDLE;
	changeState(&mTrackState);
}

void PlayerModel::Update(float dt) {

	if (!World::GetInstance()->GetSpline()) { return;  }

	mPlayerState->Update(dt);
}	

void PlayerModel::UpdatePosition(float dt) {

	SplineModel* spline = World::GetInstance()->GetSpline();

	mCurrentSplineTime = clamp(mCurrentSplineTime + mSplineTimeSpeed * dt, 0.0f, spline->MaxTime());

	SplineModel::Plane p = World::GetInstance()->GetSpline()->PlaneAt(mCurrentSplineTime);
	float trackPieceWidth = SplineFactory::trackWidth / 3;
	SetPosition(p.position + vec3(0, PlayerModel::MODEL_SPACE_HEIGHT_OFFSET, 0) + World::GetInstance()->GetSpline()->TrackShiftDir(mTrack, mCurrentSplineTime) * trackPieceWidth);
	vec3 j = vec3(0, 1, 0);
	vec3 B = normalize(cross(p.tangent, p.normal));

	bool uphill = dot(j, p.tangent) > 0;
	float rotation = degrees(acos(dot(B, j))) * (uphill ? -1 : 1);

	quat quat1 = angleAxis(270.0f, vec3(0,1,0));
	quat quat2 = angleAxis(rotation, p.normal);

	quat quatRotation = quat2 * quat1;
	SetRotation(axis(quatRotation), angle(quatRotation));
}

void PlayerModel::changeState(PlayerState* state) {
	state->setup();
	mPlayerState = state;
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
		mPlayer.changeState(&mPlayer.mMoveState);
	}
}

void TrackState::Draw() { mPlayer.DrawPlayer(); }

void MoveState::SetTrackMove(Track dir) {
	mDir = dir;
}

void MoveState::Update(float dt) {

	PlayerState::Update(dt);
	//mPlayer.UpdatePosition(dt);

	float trackPieceWidth = SplineFactory::trackWidth / 3;
	vec3 trackShift = World::GetInstance()->GetSpline()->TrackShiftDir(mDir,mCurrentTime) * mPlayer.mMoveSpeed * mCurrentTime;

	mPlayer.UpdatePosition(dt);
	mPlayer.SetPosition(mPlayer.GetPosition() + trackShift);

	vec3 j = vec3(0, 1, 0);
	
	SplineModel::Plane p = World::GetInstance()->GetSpline()->PlaneAt(mCurrentTime);
	vec3 B = normalize(cross(p.tangent, p.normal));
	bool uphill = dot(j, p.tangent) > 0;
	float rotation = degrees(acos(dot(B, j))) * (uphill ? -1 : 1);
	quat quatUD = angleAxis(rotation, vec3(1, 0, 0));
	vec3 UpDown = rotate(quatUD, vec3(0, 0, 1));

	quat quatLeft = angleAxis(-45.0f, normalize(vec3(0, 0, -1)*UpDown));
	quat quatRight = angleAxis(45.0f, normalize(vec3(0, 0, -1)*UpDown));

	if (mDir == TRACK_LEFT)
	{
		float per = clamp((length(trackShift) / trackPieceWidth), 0.0f, 1.0f);
		if (per <= 0.65f)
		{ 
			float c = per / 0.65f;
			quat InitPlayer = angleAxis(mPlayer.GetRotationAngle(), mPlayer.GetRotationAxis());
			quat quatRotationLeft = quatLeft * InitPlayer;
			quat quatRotationMove = slerp(InitPlayer, quatRotationLeft, c);
			mPlayer.SetRotation(axis(quatRotationMove), angle(quatRotationMove));
		}
		else if (per < 0.95f)
		{
			float c = per / 0.95f;
			quat InitPlayer = angleAxis(mPlayer.GetRotationAngle(), mPlayer.GetRotationAxis());
			quat quatRotationLeft = quatLeft * InitPlayer;
			quat quatRotationMove = slerp(quatRotationLeft, InitPlayer, c);
			mPlayer.SetRotation(axis(quatRotationMove), angle(quatRotationMove));
		}
		else if (per >= 0.95f)
		{
			int next = (int)mPlayer.mTrack + (mDir == TRACK_LEFT ? -1 : 1);
			Track nextTrack = (Track)clamp(next, 0, 2);
			mPlayer.mTrack = nextTrack;
			mPlayer.changeState(&mPlayer.mTrackState);
		}
	}
	else if (mDir == TRACK_RIGHT)
	{
		float per = clamp((length(trackShift) / trackPieceWidth), 0.0f, 1.0f);
		if (per <= 0.65f)
		{ 
			float c = per / 0.65f;
			quat InitPlayer = angleAxis(mPlayer.GetRotationAngle(), mPlayer.GetRotationAxis());
			quat quatRotationRight = quatRight * InitPlayer;
			quat quatRotationMove = slerp(InitPlayer, quatRotationRight, c);
			mPlayer.SetRotation(axis(quatRotationMove), angle(quatRotationMove));
		}
		else if (per < 0.95f)
		{
			float c = per / 0.95f;
			quat InitPlayer = angleAxis(mPlayer.GetRotationAngle(), mPlayer.GetRotationAxis());
			quat quatRotationRight = quatRight * InitPlayer;
			quat quatRotationMove = slerp(quatRotationRight, InitPlayer, c);
			mPlayer.SetRotation(axis(quatRotationMove), angle(quatRotationMove));
		}
		else if (per >= 0.95f)
		{
			int next = (int)mPlayer.mTrack + (mDir == TRACK_LEFT ? -1 : 1);
			Track nextTrack = (Track)clamp(next, 0, 2);
			mPlayer.mTrack = nextTrack;
			mPlayer.changeState(&mPlayer.mTrackState);
		}
	}
}

void MoveState::Draw() { mPlayer.DrawPlayer(); }

void DeadState::Draw() { mPlayer.DrawPlayer(); }

void GoalState::Draw() { mPlayer.DrawPlayer(); }
