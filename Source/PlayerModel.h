#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include "ObjectModel.h"
#include "SplineModel.h"

// Define Colors for Player Jet
#define JET_COLOR glm::vec3(0, 0, 0)
#define JET_COLOR2 glm::vec3(1, 1, 0)

class PlayerState;
class PlayerModel;

class PlayerState {

public:
	PlayerState(PlayerModel& player) : mPlayer(player), mCurrentTime(0) {}
	virtual ~PlayerState(){}
	virtual void setup() { mCurrentTime = 0; }

	virtual void Update(float dt) = 0 { mCurrentTime += dt; }
	virtual void Draw() = 0;

	float GetCurrentTime() { return mCurrentTime; }
protected:
	PlayerModel& mPlayer;
	float mCurrentTime;
};

class TrackState : public PlayerState {

public:	
	TrackState(PlayerModel& player) : PlayerState(player), mFirstPress(false) {}
	virtual void setup();
	virtual void Update(float dt);
	virtual void Draw();

private:
	bool mFirstPress;
};

class MoveState : public PlayerState {
public:
	MoveState(PlayerModel& player) : PlayerState(player) {}
	virtual void Update(float dt);
	virtual void Draw();

	void SetTrackMove(Track dir);
private:
	Track mDir;
};

class DeadState : public PlayerState {
public:
	DeadState(PlayerModel& player) : PlayerState(player) {}
	virtual void Update(float dt) { PlayerState::Update(dt); }
	virtual void Draw();
};

class GoalState : public PlayerState {
public:
	GoalState(PlayerModel& player) : PlayerState(player) {}
	virtual void Update(float dt) { PlayerState::Update(dt); }
	virtual void Draw();
};

class PlayerModel : public ObjectModel {

public:
	const static float DEFAULT_SPLINE_TIME_SPEED;
	const static float DEFAULT_MOVE_SPEED;
	const static float MODEL_SPACE_HEIGHT_OFFSET;

	static const glm::vec3 JET_SHAPE_COLORS[];

	PlayerModel();
		
	void Reset();

	virtual void Update(float dt);
	virtual void Draw() { mPlayerState->Draw(); }

	float GetCurrentSplineTime() { return mCurrentSplineTime; }

	void Died() { changeState(&mDeadState); }
	bool IsDead() { return mPlayerState == &mDeadState; }

	void ReachedGoal() { changeState(&mGoalState); }
	bool HasReachedGoal() { return mPlayerState == &mGoalState;  }

	/**
	 * Returns the current time since the player died or reached the goal. 
	 * Returns 0 if the player is not dead or has not reached the goal.
	 */
	float GetStateCurrentTime() { return IsDead() || HasReachedGoal() ? mPlayerState->GetCurrentTime() : 0; }
private:
	void UpdatePosition(float dt);
	void DrawPlayer() { ObjectModel::Draw(); }
	
	void changeState(PlayerState* state);
private:

	float mCurrentSplineTime;
	float mSplineTimeSpeed;
	float mMoveSpeed;

	glm::vec3 mSplineTrackOffset;

	Track mTrack;

	PlayerState* mPlayerState;
	TrackState mTrackState;
	MoveState mMoveState;
	DeadState mDeadState;
	GoalState mGoalState;

	friend TrackState;
	friend MoveState;
	friend DeadState;
	friend GoalState;
};


#endif
