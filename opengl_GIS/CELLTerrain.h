#pragma once

#include    "CELLQuadTree.h"
#include    "CELLContext.hpp"
#include    "CELLTerrainInterface.hpp"
#include    "CELLTaskSystem.hpp"
#include    "CELLTextureMgr.hpp"
namespace   CELL
{
    class CELLTerrain 
        :public CELLObject
        ,public CELLTerrainInterface
        ,public CELLTaskObserver
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
        typedef std::map<std::string,CELLQuadTree*>     MapNode;
        typedef std::vector<P3U3>                       ArrayVertex;
        typedef std::vector<FaceIndex>                  ArrayFace;
    public:
        CELLQuadTree*   _root;
        CELLContext&    _context;
        char            _path[CELL_PATH_LENGHT];
        CELLTaskSystem  _taskSystem;
        ArrayTask       _tasks;
        CELLMutex       _mutex;
        MapNode         _nodes;
        ArrayVertex     _vertex;
        ArrayFace       _facees;
        CELLTextureMgr  _textureMgr;
        Counts          _counts;
    public:
        CELLTerrain(CELLContext& context);
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
        virtual void    update(CELLContext& context);
        /// <summary>
        /// 绘制
        /// </summary>
        virtual void    render(CELLContext& context);
        /// <summary>
       /// 获取统计信息
       /// </summary>

        virtual Counts& getCounts();
        /// <summary>
        /// 绘制方式1,顶点数据打包
        /// </summary>
        virtual void    renderPackVertex(CELLContext& context);

    public:
        /// <summary>
        /// 创建纹理
        /// </summary>
        virtual uint    createTexture(const TileId& id);
        /// <summary>
        /// 释放纹理
        /// </summary>
        virtual void    request(CELLQuadTree* node);
        /// <summary>
        /// 释放纹理
        /// </summary>
        virtual void    cancelRequest(CELLQuadTree* node);

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
        void    calcVertexBuffer(CELLQuadTree::ArrayNode& nodes,ArrayVertex& vertx);
        void    calcIndex(CELLQuadTree::ArrayNode& nodes);
    };
}


