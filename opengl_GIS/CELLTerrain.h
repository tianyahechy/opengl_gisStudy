#pragma once

#include    "lifeiQuadTree.h"
#include    "lifeiContext.h"
#include    "lifeiTerrainInterface.h"
#include    "lifeiTaskSystem.h"
#include    "lifeiTextureMgr.h"

namespace   CELL
{
	class IPluginTileManager;
    class CELLTerrain 
        :public lifeiObject
        ,public lifeiTerrainInterface
        ,public lifeiTaskObserver
    {
    public:
        struct  P3U3
        {
            float x, y, z;
            float u, v, w;
        };

        struct  FaceIndex
        {
            short   x,y,z;
        };
    public:
        typedef std::vector<lifeiTask*>  ArrayTask;
        typedef std::map<std::string,lifeiQuadTree*>     MapNode;
        typedef std::vector<P3U3>                       ArrayVertex;
        typedef std::vector<FaceIndex>                  ArrayFace;
    public:
		lifeiQuadTree*   _root;
        lifeiContext&    _context;
        lifeiTaskSystem  _taskSystem;
        ArrayTask       _tasks;
        lifeiMutex       _mutex;
        MapNode         _nodes;
        ArrayVertex     _vertex;
        ArrayFace       _facees;
        lifeiTextureMgr  _textureMgr;
        lifeiCounts          _counts;

		IPluginTileManager * _tileSourcePlugin;
		HMODULE				_hTileSourceDll;
    public:
        CELLTerrain(lifeiContext& context);
        ~CELLTerrain();

		//加载场景
		virtual bool loadScene(const char* fileName);
        /// <summary>
        /// 创建节点
        /// </summary>
        virtual void    initailze();
        /// <summary>
        /// 更新接口
        /// </summary>
        virtual void    update(lifeiContext& context);
        /// <summary>
        /// 绘制
        /// </summary>
        virtual void    render(lifeiContext& context);
        /// <summary>
       /// 获取统计信息
       /// </summary>

        virtual lifeiCounts& getCounts();
        /// <summary>
        /// 绘制方式1,顶点数据打包
        /// </summary>
        virtual void    renderPackVertex(lifeiContext& context);

    public:
        /// <summary>
        /// 释放纹理
        /// </summary>
        virtual void    request(lifeiQuadTree* node);
        /// <summary>
        /// 释放纹理
        /// </summary>
        virtual void    cancelRequest(lifeiQuadTree* node);

        /// <summary>
        /// 释放纹理
        /// </summary>
        virtual void    releaseTexture(uint texId);   
    public:
        /// <summary>
        /// 任务取消通知
        /// </summary>
        virtual void    onTaskCancel(lifeiTask* task);
        /// <summary>
        /// 任务完成通知
        /// </summary>
        virtual void    onTaskExe(lifeiTask* task);
        /// <summary>
        /// 任务完成通知
        /// </summary>
        virtual void    onTaskFinish(lifeiTask* task);
    protected:
        void    calcVertexBuffer(lifeiQuadTree::ArrayNode& nodes,ArrayVertex& vertx);

		IPluginTileManager * createTileSourceDLL(const char* dllFileName);
    };
}


