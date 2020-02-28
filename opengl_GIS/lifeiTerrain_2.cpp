
#include "lifeiTerrain_2.h"
#include "LifeiProgramLibrary.h"
#include "lifeiTileTask_2.h"
#include "lifeiTimeStamp.hpp"
#include "rapidxml.hpp"
#include "IPluginTileManager.h"
#include "lifeiShaderManager_2.h"

namespace CELL
{
	lifeiTerrain_2::lifeiTerrain_2(lifeiContext & context)
		: _context(context),
		_textureMgr(_context)
	{
		_tileSourcePlugin = 0;
		_hTileSourceDll = 0;
		_root = 0;
		_taskSystem.setObserver(this);
		_vertexVector.reserve(1024 * 4);
		_textureMgr.initialize();
		_counts._nodes = 0;
		_counts._drawNodes = 0;
		_counts._texCounts = sizeof(_textureMgr._used);
		_counts._texFree = _textureMgr.getFreeCount();
		_counts._texUsed = _textureMgr.getUsedCount();
	}

	lifeiTerrain_2::~lifeiTerrain_2()
	{
		delete _root;
	}

	bool lifeiTerrain_2::loadScene(const char * fileName)
	{
		rapidxml::xml_document<> doc;
		FILE* file = fopen(fileName, "rb");
		if ( 0 == file )
		{
			return false;
		}

		fseek(file, 0, SEEK_END);
		size_t nSize = ftell(file);
		fseek(file, 0, SEEK_SET);
		char * pBuf = new char[nSize + 1];
		memset(pBuf, 0, nSize + 1);
		fread(pBuf, nSize, 1, file);
		pBuf[nSize] = '\0';
		fclose(file);


		try
		{
			do
			{
				doc.parse<0>(pBuf);
				rapidxml::xml_node<> * pRoot = doc.first_node();
				rapidxml::xml_node<> * pImageSource = pRoot->first_node();
				if ( 0 == pImageSource)
				{
					break;
				}
				rapidxml::xml_attribute<> * pDll = pImageSource->first_attribute("loader");
				if ( 0 == pDll)
				{
					break;
				}
				_tileSourcePlugin = createTileSourceDLL(pDll->value());
				if ( 0 == _tileSourcePlugin)
				{
					break;
				}
				rapidxml::xml_attribute<> * pAttr = pImageSource->first_attribute();
				for (; pAttr; pAttr = pAttr->next_attribute())
				{
					_tileSourcePlugin->setParam(pAttr->name(), pAttr->value());
				}
			} while (false);

			//初始化，启动线程
			initialize();
		}
		catch (const std::exception&)
		{
			
		}
		delete[] pBuf;
		return false;
	}

	void lifeiTerrain_2::initialize()
	{
		_taskSystem.start(4);
		_root = new lifeiQuadTree_2(this, NULL, real2(-20037508, -20037508), real2(20037508, 20037508), 0, lifeiQuadTree_2::CHILD_LT);
	}

	void lifeiTerrain_2::update(lifeiContext & context)
	{
		if ( 0 == _root)
		{
			return;
		}
		_root->update(context);
		//取出要绘制的瓦片数组
		arrayTask tasksDrawing;
		{
			lifeiMutex_2::ScopeLock lk(_mutex);
			tasksDrawing = _tasksLoaded;
			_tasksLoaded.clear();
		}

		for (size_t i = 0; i < tasksDrawing.size(); i++)
		{
			lifeiTileTask_2 * pTask = dynamic_cast<lifeiTileTask_2*> (tasksDrawing[i]);
			if ( 0 == pTask )
			{
				delete tasksDrawing[i];
				continue;
			}

			char szBuf[128];
			sprintf(szBuf, "%d-%d-%d:%p", pTask->_tileId._lev, pTask->_tileId._row, pTask->_tileId._col, pTask->_node);
			mapQuadTreeNode::iterator itr = _quadTreeNodeSet.find(szBuf);
			if (itr == _quadTreeNodeSet.end() )
			{
				delete pTask;
				continue;
			}
			else
			{
				_quadTreeNodeSet.erase(itr);
			}
			//查询节点是否存在
			uint texIndex = _textureMgr.allocTexture();
			pTask->_node->updateTexture(texIndex);
			_textureMgr.updateTexture(texIndex, pTask->_image.data());
			delete pTask;
		}
	}

	void lifeiTerrain_2::render(lifeiContext & context)
	{
		renderPackVertex(context);
	}

	lifeiCounts & lifeiTerrain_2::getCounts()
	{
		// TODO: 在此处插入 return 语句
		return _counts;
	}

	void lifeiTerrain_2::renderPackVertex(lifeiContext & context)
	{
		if ( 0 == _root)
		{
			return;
		}
		//获得绘制的所有节点
		lifeiQuadTree_2::arrayNode nodes;
		_root->getAllRenderableNode(nodes);
		getCounts()._drawNodes = (uint)nodes.size();
		getCounts()._texUsed = _textureMgr.getUsedCount();
		getCounts()._texFree = _textureMgr.getFreeCount();

		if (nodes.empty())
		{
			return;
		}

		//对节点进行绘制
		lifeiTimeStamp tm;
		//获取shader
		PROGRAM_P3_U3_TEXARRAY& prg = context._shaderMgr->_program_P3_U3_TEXTARRAY;
		//根据四叉树可绘制的节点得到绘制的顶点数组
		calcVertexBuffer(nodes, _vertexVector);
		context._device->bindTextureArray(&_textureMgr._textureId);

		prg.begin();
		if (_vertexVector.size())
		{
			context._device->setUniformMatrix4fv(prg._mvp, 1, false, context._vp.dataPtr());
			context._device->setUniform1i(prg._texture, 0);
			context._device->attributePointer(prg._position, 3, GL_FLOAT, GL_FALSE, sizeof(P3U3), &_vertexVector[0].x);
			context._device->attributePointer(prg._uv, 3, GL_FLOAT, GL_FALSE, sizeof(P3U3), &_vertexVector[0].u);
			context._device->drawArrays(GL_TRIANGLES, 0, _vertexVector.size());
		}
		prg.end();
		
		//获得每帧渲染时长
		double theTime = tm.getElapsedTimeInMilliSec();
		char szBuf[1024];
		sprintf(szBuf, "node = %d draw = %d free = %d, %lf ms\n",
			_counts._nodes,
			_counts._drawNodes,
			_counts._texFree,
			theTime);
		OutputDebugStringA(szBuf);

	}

	void lifeiTerrain_2::request(lifeiQuadTree_2 * node)
	{
		lifeiTileTask_2 * pTask = new lifeiTileTask_2();
		pTask->_node = node;
		pTask->_tileId = node->_tileID;
		_taskSystem.addTask(pTask);

		char szBuf[128];
		sprintf(szBuf, "%d-%d-%d:%p", pTask->_tileId._lev, pTask->_tileId._row, pTask->_tileId._col, pTask->_node);
		mapQuadTreeNode::iterator itr = _quadTreeNodeSet.find(szBuf);
		if (itr != _quadTreeNodeSet.end())
		{
			return;
		}
		_quadTreeNodeSet[szBuf] = node;
	}

	void lifeiTerrain_2::cancelRequest(lifeiQuadTree_2 * node)
	{
		char szBuf[128];
		sprintf(szBuf, "%d-%d-%d:%p", node->_tileID._lev, node->_tileID._row, node->_tileID._col, node);
		mapQuadTreeNode::iterator itr = _quadTreeNodeSet.find(szBuf);
		if (itr != _quadTreeNodeSet.end())
		{
			_quadTreeNodeSet.erase(itr);
		}
	}

	void lifeiTerrain_2::releaseTexture(unsigned int texId)
	{
		_textureMgr.freeTexture(texId);
	}

	void lifeiTerrain_2::onTaskCancel(lifeiTask_2 * task)
	{
		delete task;
	}

	void lifeiTerrain_2::onTaskExe(lifeiTask_2 * task)
	{
		lifeiTask_2* pTask = dynamic_cast<lifeiTask_2*> (task);
		if ( 0 == pTask)
		{
			return;
		}
		if ( 0 == _tileSourcePlugin)
		{
			delete task;
			return;
		}

		if ( 0 == _tileSourcePlugin->load(task))
		{
			delete task;
			return;
		}

		//存储要绘制的数组
		lifeiMutex_2::ScopeLock lk(_mutex);
		_tasksLoaded.push_back(pTask);
	}

	void lifeiTerrain_2::onTaskFinish(lifeiTask_2 * task)
	{
	}

	void lifeiTerrain_2::calcVertexBuffer(lifeiQuadTree_2::arrayNode & nodes, arrayVertex & vertex)
	{
		vertex.resize(nodes.size() * 6);
		P3U3 * vPlane = &vertex.front();
		for (size_t i = 0; i < nodes.size(); i++)
		{
			lifeiQuadTree_2* pNode = nodes[i];
			real2 startXY = pNode->_startXY;
			real2 endXY = pNode->_endXY;

			float2 uvStart = pNode->_uvStart;
			float2 uvEnd = pNode->_uvEnd;

			vPlane[0].x = startXY.x;
			vPlane[0].y = 0;
			vPlane[0].z = endXY.y;
			vPlane[0].u = uvStart.x;
			vPlane[0].v = uvEnd.y;
			vPlane[0].w = pNode->_textureID;

			vPlane[1].x = endXY.x;
			vPlane[1].y = 0;
			vPlane[1].z = endXY.y;
			vPlane[1].u = uvEnd.x;
			vPlane[1].v = uvEnd.y;
			vPlane[1].w = pNode->_textureID;

			vPlane[2].x = endXY.x;
			vPlane[2].y = 0;
			vPlane[2].z = startXY.y;
			vPlane[2].u = uvEnd.x;
			vPlane[2].v = uvStart.y;
			vPlane[2].w = pNode->_textureID;

			vPlane[3].x = startXY.x;
			vPlane[3].y = 0;
			vPlane[3].z = endXY.y;
			vPlane[3].u = uvStart.x;
			vPlane[3].v = uvEnd.y;
			vPlane[3].w = pNode->_textureID;

			vPlane[4].x = endXY.x;
			vPlane[4].y = 0;
			vPlane[4].z = startXY.y;
			vPlane[4].u = uvEnd.x;
			vPlane[4].v = uvStart.y;
			vPlane[4].w = pNode->_textureID;

			vPlane[5].x = startXY.x;
			vPlane[5].y = 0;
			vPlane[5].z = startXY.y;
			vPlane[5].u = uvStart.x;
			vPlane[5].v = uvStart.y;
			vPlane[5].w = pNode->_textureID;

			vPlane += 6;

		}
	}

	IPluginTileManager * lifeiTerrain_2::createTileSourceDLL(const char * dllFileName)
	{
		HMODULE hDll = LoadLibraryA(dllFileName);
		if ( 0 == hDll)
		{
			return NULL;
		}

		CREATETILESOURCEFUNC func = (CREATETILESOURCEFUNC)GetProcAddress(hDll, CREATE_TILESOURCEDLL);
		if (NULL == func)
		{
			CloseHandle(hDll);
			return NULL;
		}
		_hTileSourceDll = hDll;
		return func(0);
	}


	

}
