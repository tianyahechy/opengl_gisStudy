
#pragma once
#include "lifeiQuadTree_2.h"
#include "lifeiContext_2.h"
#include "lifeiTerrainInterface_2.h"
#include "lifeiTaskSystem_2.h"
#include "lifeiTextureMgr_2.h"
#include <string>

namespace CELL
{
	class IPluginTileManager;
	class lifeiTerrain_2 : public lifeiObject_2, public lifeiTerrainInterface_2, public lifeiTaskObserver_2
	{
		struct P3U3
		{
			float x, y, z;
			float u, v, w;
		};

	public:
		typedef std::vector<lifeiTask_2*>				arrayTask;
		typedef std::map<std::string, lifeiQuadTree_2*>	mapQuadTreeNode;
		typedef std::vector<P3U3>						arrayVertex;
		
	public:
		lifeiQuadTree_2*								_root;
		lifeiContext_2&									_context;
		lifeiTaskSystem_2								_taskSystem;
		arrayTask										_tasksLoaded;	//已生成瓦片纹理的任务数组，
		lifeiMutex_2									_mutex;
		mapQuadTreeNode									_quadTreeNodeSet;//已生成瓦片纹理的四叉树集合
		arrayVertex										_vertexVector;
		lifeiTextureMgr_2								_textureMgr;
		lifeiCounts										_counts;
		
		IPluginTileManager*								_tileSourcePlugin;
		HMODULE											_hTileSourceDll;

	public:
		lifeiTerrain_2(lifeiContext_2& context);
		~lifeiTerrain_2();

		//加载场景
		virtual bool loadScene(const char* fileName);
		//创建节点
		virtual void initialize();
		//更新要绘制的瓦片数据
		virtual void update(lifeiContext_2& context);
		//绘制
		virtual void render(lifeiContext_2& context);
		//获取统计信息
		virtual lifeiCounts& getCounts();
		//绘制方式1，顶点数据打包
		virtual void renderPackVertex(lifeiContext_2& context);

	public:
		//将四叉树节点node的属性加入生成瓦片任务系统，获取相应的瓦片数据
		virtual void request(lifeiQuadTree_2* node);
		///将四叉树节点node的属性从生成瓦片任务系统中移除
		virtual void cancelRequest(lifeiQuadTree_2* node);
		//释放纹理
		virtual void releaseTexture(unsigned int texId);

	public:
		//任务取消通知
		virtual void onTaskCancel(lifeiTask_2* task);
		//任务执行通知
		virtual void onTaskExe(lifeiTask_2* task);
		//任务完成通知
		virtual void onTaskFinish(lifeiTask_2* task);

	protected:
		//根据四叉树节点构建三角面集合
		void calcVertexBuffer(lifeiQuadTree_2::arrayNode& nodes, arrayVertex& vertex);
		IPluginTileManager* createTileSourceDLL(const char* dllFileName);

	};
}
