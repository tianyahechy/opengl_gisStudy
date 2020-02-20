#pragma once
#include "lifeiContext.h"
#include "lifeiOpengl.h"
#include "lifeiTexture3dID.h"

namespace CELL
{
	class lifeiTextureMgr_2
	{
	public:
		lifeiContext&			_context;
		bool					_used[1024];
		lifeiTexture3dID		_textureId;

	public:
		lifeiTextureMgr_2(lifeiContext& context);
		//初始化
		virtual bool initialize();
		//查询获取,如果是-1，则无效，否则在lifeiquadtree类的析构中释放纹理
		virtual uint allocTexture();
		//释放纹理
		virtual void freeTexture(uint index);
		//更新纹理数据
		virtual void updateTexture(uint index, const void* data);
		//获取当前已经使用的纹理单元个数
		virtual uint getUsedCount();
		//获得当前剩余的纹理数量
		virtual uint getFreeCount();
	};
}
