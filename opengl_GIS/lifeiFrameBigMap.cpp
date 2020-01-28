/*

#include "lifeiPlatform.h"
#include "lifeiFrameBigMap.h"
#include "lifeiOpengl.h"
#include "lifeiContext.h"
#include "lifeiShaderManager.h"
#include "lifeiSpatialReference.h"

#define FSIZE	20037508

namespace CELL
{
	lifeiFrameBigMap::lifeiFrameBigMap(lifeiContext& context)
		:lifeiFrame(context),
		_bLbuttonDown(false),
		_terrain(_context)
	{
		_bMbuttonDown = false;
		_context._camera.setEye(real3(0, FSIZE * 2, 0));
		_context._camera.setTarget(real3(0, 0, 0));
		_context._camera.calcDir();

		_context._camera.setUp(real3(0, 0, 1));
		_context._camera.setRight(real3(1, 0, 0));
	}

	lifeiFrameBigMap::~lifeiFrameBigMap()
	{

	}
	bool lifeiFrameBigMap::loadScene(const char* fileName)
	{
		return _terrain.loadScene(fileName);
	}

	void lifeiFrameBigMap::update(lifeiContext&)
	{

	}

}
*/