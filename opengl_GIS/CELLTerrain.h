#pragma once

#include    "lifeiQuadTree.h"
#include	"lifeiObject.h"
#include    "lifeiContext.h"
#include    "lifeiTerrainInterface.h"
#include	"CELLTaskSystem.hpp"
#include	"CELLTask.hpp"
namespace   CELL
{
    class CELLTerrain 
        :public lifeiObject
        ,public lifeiTerrainInterface
		,public CELLTaskObserver
    {
	public:
		typedef std::vector<CELLTask*> ArrayTask;
		typedef std::map<std::string, lifeiQuadTree*> MapNode;
    public:
        lifeiQuadTree*  _root;
		lifeiContext&   _context;
        char            _path[CELL_PATH_LENGTH];
		CELLTaskSystem	_taskSystem;
		ArrayTask		_tasks;
		lifeiMutex		_mutex;
		MapNode		_nodes;
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
        virtual void    initialize();
        /// <summary>
        /// 更新接口
        /// </summary>
        virtual void    update(lifeiContext& context);
        /// <summary>
        /// 绘制
        /// </summary>
        virtual void    render(lifeiContext& context);
    public:
        /// <summary>
        /// 创建纹理
        /// </summary>
        virtual uint    createTexture(const TileId& id);
        /// <summary>
        /// 释放纹理
        /// </summary>
        virtual void    releaseTexture(uint texId);
		virtual void	cancelRequest(lifeiQuadTree* node);
	public:		
		//任务执行通知
		virtual void onTaskEXE(CELLTask* task);
		//任务完成通知
		virtual void onTaskFinish(CELLTask* task);
		//任务取消通知
		virtual void onTaskCancel(CELLTask* task);
		//请求数据
		virtual void request(lifeiQuadTree * node);
    };
}


