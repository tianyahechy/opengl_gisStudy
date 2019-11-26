#include "CELLTerrain.h"
#include "CELLResourceMgr.hpp"
#include "LifeiProgramLibrary.h"
#include "CELLTileTask.hpp"

namespace CELL
{
    CELLTerrain::CELLTerrain(lifeiContext& context)
        :_context(context)
    {
        _root   =   0;
		_taskSystem.setObserver(this);
    }


    CELLTerrain::~CELLTerrain()
    {
        delete  _root;
    }

    void CELLTerrain::setTileSourcePath(const char* pathName)
    {
        strncpy(_path, pathName, sizeof(_path));
    }

    void CELLTerrain::initialize()
    {
		_taskSystem.start(4);
        _root = new lifeiQuadTree(this, 0, real2(-20037508, -20037508), real2(20037508, 20037508), 0, lifeiQuadTree::CHILD_LT);
    }

    void CELLTerrain::update(lifeiContext& context)
    {
        _root->update(context);
		ArrayTask tasks;
		{
			lifeiMutex::ScopeLock lk(_mutex);
			tasks = _tasks;
			_tasks.clear();
		}
		for (size_t i = 0; i < tasks.size(); i++)
		{
			CELLTileTask* pTask = dynamic_cast<CELLTileTask*> (tasks[i]);
			if ( 0 == pTask)
			{
				delete tasks[i];
				continue;
			}

			char szBuf[128];
			sprintf(szBuf, "%d-%d-%d:%p", pTask->_tileId._lev, pTask->_tileId._row, pTask->_tileId._col, pTask->_node);
			MapNode::iterator itr = _nodes.find(szBuf);
			if (itr == _nodes.end())
			{
				delete pTask;
				continue;
			}
			else
			{
				_nodes.erase(itr);
			}
			//查询节点是否存在
			Texture2dId texId = _context._resMgr->createTexture2dFromImage(pTask->_image);
			pTask->_node->updateTexture(texId._texture);
			
			delete pTask;
		}
    }

    void CELLTerrain::render(lifeiContext& context)
    {
        lifeiQuadTree::ArrayNode nodes;
        _root->getAllRenderableNode(nodes);

        /// 对节点进行绘制

        /// 获取shader
        PROGRAM_P3_U2&  prg = context._resMgr->_PROGRAM_P3_U2;
        struct  P3U2
        {
            float x, y, z;
            float u, v;
        };
        P3U2  vPlane[4];
        prg.begin();
        {
            for (size_t i = 0 ;i < nodes.size() ; ++ i)
            {
                lifeiQuadTree*  pNode   =   nodes[i];
                real2           vStart  =   pNode->_vStart;
                real2           vEnd    =   pNode->_vEnd;
				float2			uvStart =	pNode->_uvStart;
				float2			uvEnd = pNode->_uvEnd;
                vPlane[0].x     =   vStart.x;
                vPlane[0].y     =   0;
                vPlane[0].z     =   vEnd.y;
                vPlane[0].u     =   uvStart.x;
                vPlane[0].v     =   uvEnd.y;

                vPlane[1].x     =   vEnd.x;
                vPlane[1].y     =   0;
                vPlane[1].z     =   vEnd.y;
                vPlane[1].u     =   uvEnd.x;
                vPlane[1].v     =   uvEnd.y;

                vPlane[2].x     =   vEnd.x;
                vPlane[2].y     =   0;
                vPlane[2].z     =   vStart.y;
                vPlane[2].u     =   uvEnd.x;
                vPlane[2].v     =   uvStart.y;

                vPlane[3].x     =   vStart.x;
                vPlane[3].y     =   0;
                vPlane[3].z     =   vStart.y;
                vPlane[3].u     =   uvStart.x;
                vPlane[3].v     =   uvStart.y;

                Texture2dId texId;
                texId._texture  =   pNode->_textureID;
                context._device->bindTexture2D(&texId);
                context._device->setUniformMatrix4fv(prg._mvp, 1, false, context._vp.dataPtr());
                context._device->setUniform1i(prg._texture, 0);
                context._device->attributePointer(prg._position, 3, GL_FLOAT, GL_FALSE, sizeof(P3U2), &vPlane[0].x);
                context._device->attributePointer(prg._uv, 2, GL_FLOAT, GL_FALSE, sizeof(P3U2), &vPlane[0].u);


                context._device->drawArrays(GL_TRIANGLE_FAN, 0, 4);
            }
            
        }
        prg.end();

    }

    uint CELLTerrain::createTexture(const TileId& id)
    {
        char    szPathName[CELL_PATH_LENGTH];
        sprintf(szPathName,"%s/L%02d/%06d-%06d.jpg",_path,id._lev + 1,id._row,id._col);
        Texture2dId texId = _context._resMgr->createTexture2dFromImage(szPathName);
        return  texId._texture;
    }

    void CELLTerrain::releaseTexture(uint texId)
    {
        Texture2dId tex;
        tex._texture = texId;
        _context._device->destroyTexture2D(tex);
    }

	void CELLTerrain::cancelRequest(lifeiQuadTree * node)
	{
		char szBuf[128];
		sprintf(szBuf, "%d-%d-%d:%p", node->_tileID._lev, node->_tileID._row, node->_tileID._col, node);
		MapNode::iterator itr = _nodes.find(szBuf);
		if (itr != _nodes.end())
		{
			_nodes.erase(itr);
		}
	}

	void CELLTerrain::onTaskEXE(CELLTask * task)
	{
		CELLTileTask* pTask = dynamic_cast<CELLTileTask*> (task);
		if ( 0 == pTask)
		{
			return;
		}
		char    szPathName[CELL_PATH_LENGTH];
		sprintf(szPathName, "%s/L%02d/%06d-%06d.jpg", _path, pTask->_tileId._lev + 1, pTask->_tileId._row, pTask->_tileId._col);
		if (CELLImageLoader::loadImage(szPathName, pTask->_image))
		{
			lifeiMutex::ScopeLock lk(_mutex);
			_tasks.push_back(pTask);
		}
		else
		{
			delete task;
		}
	}

	void CELLTerrain::onTaskFinish(CELLTask * task)
	{
	}

	void CELLTerrain::onTaskCancel(CELLTask * task)
	{
		delete task;
	}

	void CELLTerrain::request(lifeiQuadTree * node)
	{
		CELLTileTask *pTask = new CELLTileTask;
		pTask->_node = node;
		pTask->_tileId = node->_tileID;
		_taskSystem.addTask(pTask);

		char szBuf[128];
		sprintf(szBuf, "%d-%d-%d:%p", pTask->_tileId._lev, pTask->_tileId._row, pTask->_tileId._col, pTask->_node);
		if (_nodes.find(szBuf) != _nodes.end())
		{
			return;
		}
		_nodes[szBuf] = node;
	}

}

