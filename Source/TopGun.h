#include <glm/glm.hpp>
#include <vector>
#include <list>
#include "Billboard.h"

class TopGun
{
public:

	TopGun();
	void Update(float dt);
	void Draw();
	void Reset();

	static const int MAX_TGBillboards = 5;

private:
	// New Lists
	BillboardList* mpBillboardListGoose;
	BillboardList* mpBillboardListIceman;
	BillboardList* mpBillboardListMaverick;
	BillboardList* mpBillboardListTGend;
	BillboardList* mpBillboardListTG;
};
