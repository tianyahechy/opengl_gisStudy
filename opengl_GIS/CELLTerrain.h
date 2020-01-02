#pragma once

#include    "lifeiQuadTree.h"
#include    "lifeiContext.h"
#include    "lifeiTerrainInterface.h"
#include    "lifeiTaskSystem.h"
#include    "lifeiTextureMgr.h"
namespace   CELL
{
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
        typedef std::vector<CELLTask*>  ArrayTask;
        typedef std::map<std::string,lifeiQuadTree*>     MapNode;
        typedef std::vector<P3U3>                       ArrayVertex;
        typedef std::vector<FaceIndex>                  ArrayFace;
    public:
		lifeiQuadTree*   _root;
        lifeiContext&    _context;
        char            _path[CELL_PATH_LENGTH];
        lifeiTaskSystem  _taskSystem;
        ArrayTask       _tasks;
        lifeiMutex       _mutex;
        MapNode         _nodes;
        ArrayVertex     _vertex;
        ArrayFace       _facees;
        lifeiTextureMgr  _textureMgr;
        lifeiCounts          _counts;
    public:
        CELLTerrain(lifeiContext& context);
        ~CELLTerrain();
        /// <summary>
        /// 指定数据源
        /// </summary>
        virtual void    setTileSourcePath(const char* pathName);

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
        /// 创建纹理
        /// </summary>
        virtual uint    createTexture(const TileId& id);
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
        virtual void    onTaskCancel(CELLTask* task);
        /// <summary>
        /// 任务完成通知
        /// </summary>
        virtual void    onTaskExe(CELLTask* task);
        /// <summary>
        /// 任务完成通知
        /// </summary>
        virtual void    onTaskFinish(CELLTask* task);
    protected:
        void    calcVertexBuffer(lifeiQuadTree::ArrayNode& nodes,ArrayVertex& vertx);
        void    calcIndex(lifeiQuadTree::ArrayNode& nodes);
    };
}


