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

private:
	// New Lists
	BillboardList* mpBillboardList2;
	BillboardList* mpBillboardList3;
	BillboardList* mpBillboardList4;
	BillboardList* mpBillboardList5;
	BillboardList* mpBillboardList6;
};
