#pragma once

#include "lifeiQuadTree.h"
#include "lifeiContext.h"
#include "lifeiTerrainInterface.h"
#include "lifeiTaskSystem.h"
#include "lifeiTextureMgr.h"

namespace CELL
{
	class IPluginTileManager;

	class lifeiTerrain : public lifeiObject, public lifeiTerrainInterface, public lifeiTaskObserver
	{
	public:
		struct P3U3
		{
			float x, y, z;
			float u, v, w;
		};

		struct FaceIndex
		{
			short x, y, z;
		};
	public:
		typedef std::vector<lifeiTask*>							arrayTask;
		typedef std::map<std::string, lifeiQuadTree*>			mapNode;
		typedef std::vector<P3U3>								arrayVertex;
		typedef std::vector<FaceIndex>							arrayFace;

	public:
		lifeiQuadTree*											_root;
		lifeiContext&											_context;
		lifeiTaskSystem											_taskSystem;
		arrayTask												_tasks;
		lifeiMutex												_mutex;
		mapNode													_nodes;
		arrayVertex												_vertex;
		arrayFace												_faces;
		lifeiTextureMgr											_textureMgr;
		lifeiCounts												_counts;

		IPluginTileManager	*									_tileSourcePlugin;
		HMODULE													_hTileSourceDll;

	public:
		lifeiTerrain(lifeiContext& context);
		~lifeiTerrain();

		//加载场景
		virtual bool loadScene(const char* fileName);
		//创建节点
		virtual void initialize();
		//更新接口
		virtual void update(lifeiContext& context);
		//绘制
		virtual void render(lifeiContext& context);
		//获取统计信息
		virtual lifeiCounts& getCounts();

		//绘制方式1，顶点数据打包
		virtual void renderPackVertex(lifeiContext& context);

	public:
		virtual void request(lifeiQuadTree* node);
		virtual void cancelRequest(lifeiQuadTree* node);
		//释放纹理
		virtual void releaseTexture(uint texId);

	public:
		//任务取消通知
		virtual void onTaskCancel(lifeiTask* task);
		//任务执行通知
		virtual void onTaskExe(lifeiTask* task);
		//任务完成通知
		virtual void onTaskFinish(lifeiTask* task);

	protected:
		void calcVertexBuffer(lifeiQuadTree::ArrayNode& nodes, arrayVertex& vertex);

		IPluginTileManager* createTileSourceDLL(const char* dllFileName);


	};

}