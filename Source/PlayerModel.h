#ifndef PLAYERMODEL_H
#define PLAYERMODE_H

#include "ObjectModel.h"

class PlayerState;
class PlayerModel;

enum Track { TRACK_LEFT, TRACK_MIDDLE, TRACK_RIGHT };

class PlayerState {

public:
	PlayerState(PlayerModel& player) : mPlayer(player), mCurrentTime(0) {}
	virtual ~PlayerState(){}

	virtual void setup() { mCurrentTime = 0; }

	virtual void Update(float dt) = 0 { mCurrentTime += dt; }

protected:
	PlayerModel& mPlayer;
	float mCurrentTime;
};

class TrackState : public PlayerState {

public:	
	TrackState(PlayerModel& player) : PlayerState(player), mFirstPress(false) {}
	virtual void setup();
	virtual void Update(float dt);

private:
	bool mFirstPress;
};

class MoveState : public PlayerState {
public:
	MoveState(PlayerModel& player) : PlayerState(player) {}
	virtual void Update(float dt);

	void SetTrackMove(Track dir);
private:
	Track mDir;
};

class PlayerModel : public ObjectModel {

public:
	const static float DEFAULT_SPLINE_TIME_SPEED;
	const static float DEFAULT_MOVE_SPEED;
	const static float MODEL_SPACE_HEIGHT_OFFSET;

	static const glm::vec3 SHEEP_SHAPE_COLORS[];

	PlayerModel();
		
	virtual void Update(float dt);

private:
	void UpdatePosition(float dt);
	glm::vec3 TrackShiftDir(Track dir);

private:

	float mCurrentSplineTime;
	float mSplineTimeSpeed;
	float mMoveSpeed;

	glm::vec3 mSplineTrackOffset;

	Track mTrack;

	PlayerState* mPlayerState;
	TrackState mTrackState;
	MoveState mMoveState;

	friend TrackState;
	friend MoveState;
};


#endif
