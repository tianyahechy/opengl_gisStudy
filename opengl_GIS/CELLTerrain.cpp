#include "CELLTerrain.h"
#include "CELLResourceMgr.hpp"
#include "CELLProgramLibary.hpp"
#include "CELLTileTask.hpp"
#include "CELLTimestamp.hpp"

namespace CELL
{
    CELLTerrain::CELLTerrain(CELLContext& context)
        :_context(context)
        ,_textureMgr(_context)
    {
        _root   =   0;
        _taskSystem.setObserver(this);
        _vertex.reserve(1024*4);
        _facees.reserve(1024 * 4);
        _textureMgr.initialize();
        _counts._nodes  =   0;
        _counts._drawNodes  =   0;
        _counts._textCounts =   sizeof(_textureMgr._used);
        _counts._texFree    =   _textureMgr.getFreeCount();
        _counts._texUsed    =   _textureMgr.getUsedCount();
    }

    CELLTerrain::~CELLTerrain()
    {
        delete  _root;
    }

    void CELLTerrain::setTileSourcePath(const char* pathName)
    {
        strncpy(_path, pathName, sizeof(_path));
    }

    void CELLTerrain::initailze()
    {
        _taskSystem.start(4);
        _root = new CELLQuadTree(this, 0, real2(-20037508, -20037508), real2(20037508, 20037508), 0, CELLQuadTree::CHILD_LT);
    }

    void CELLTerrain::update(CELLContext& context)
    {
        _root->update(context);
        ArrayTask   tasks;
        {
            CELLMutex::ScopeLock lk(_mutex);
            tasks   =   _tasks;
            _tasks.clear();
        }
        for (size_t i = 0 ;i < tasks.size() ; ++ i)
        {
            CELLTileTask*   pTask   =   dynamic_cast<CELLTileTask*>(tasks[i]);
            if (pTask == 0)
            {
                delete  tasks[i];
                continue;
            }
            char    szBuf[128];
            sprintf(
                szBuf
                , "%d-%d-%d:%p"
                , pTask->_tileId._lev
                , pTask->_tileId._row
                , pTask->_tileId._col
                , pTask->_node);

            MapNode::iterator itr = _nodes.find(szBuf);
            if (itr == _nodes.end())
            {
                delete  pTask;
                continue;
            }
            else
            {
                _nodes.erase(itr);
            }
            /// 查询节点是否存在
            uint    texIndex    =   _textureMgr.allocTexture();
            pTask->_node->updateTexture(texIndex);
             
            _textureMgr.updateTexture(texIndex,pTask->_image.data());
            delete  pTask;
        }
    }

    void CELLTerrain::render(CELLContext& context)
    {
        renderPackVertex(context);
    }

    CELL::Counts& CELLTerrain::getCounts()
    {
        return  _counts;
    }

    void CELLTerrain::renderPackVertex(CELLContext& context)
    {
        CELLQuadTree::ArrayNode nodes;
        _root->getAllRenderableNode(nodes);
        getCounts()._drawNodes  =   (uint)nodes.size();
        getCounts()._texUsed    =   _textureMgr.getUsedCount();
        getCounts()._texFree    =   _textureMgr.getFreeCount();

        if (nodes.empty())
        {
            return;
        }
        /// 对节点进行绘制
        CELLTimestamp   tm;
        /// 获取shader
        PROGRAM_P3_U3_TEXARRAY&  prg = context._resMgr->_PROGRAM_P3_U3_TEXARRAY;
        
        
        calcVertexBuffer(nodes,_vertex);
        context._device->bindTextureArray(&_textureMgr._textureId);
        prg.begin();
        if (_vertex.size())
        {
            context._device->setUniformMatrix4fv(prg._mvp, 1, false, context._vp.dataPtr());
            context._device->setUniform1i(prg._texture, 0);
            context._device->attributePointer(prg._position,    3, GL_FLOAT, GL_FALSE, sizeof(P3U3), &_vertex[0].x);
            context._device->attributePointer(prg._uv,          3, GL_FLOAT, GL_FALSE, sizeof(P3U3), &_vertex[0].u);

            context._device->drawArrays(GL_TRIANGLES, 0, _vertex.size());
        }
        prg.end();

        tm.getElapsedTimeInMilliSec();
        char    szBuf[1024];

        sprintf(szBuf,"node = %d draw = %d  free = %d ,%lf ms\n"
            ,_counts._nodes
            ,_counts._drawNodes
            ,_counts._texFree
            ,tm.getElapsedTimeInMilliSec());
        OutputDebugStringA(szBuf);
    }

    uint CELLTerrain::createTexture(const TileId& id)
    {
        char    szPathName[CELL_PATH_LENGHT];
        sprintf(szPathName,"%s/L%02d/%06d-%06d.jpg",_path,id._lev + 1,id._row,id._col);
        Texture2dId texId = _context._resMgr->createTexture2dFromImage(szPathName);
        return  texId._texture;
    }
    void CELLTerrain::request(CELLQuadTree* node)
    {
        CELLTileTask*   pTask   =   new CELLTileTask();
        pTask->_node    =   node;
        pTask->_tileId  =   node->_tileId ;
        _taskSystem.addTask(pTask);

        char    szBuf[128];
        sprintf(
            szBuf
            ,"%d-%d-%d:%p"
            ,pTask->_tileId._lev
            ,pTask->_tileId._row
            ,pTask->_tileId._col
            ,pTask->_node);
        if (_nodes.find(szBuf) != _nodes.end())
        {
            return;
        }
        _nodes[szBuf]   =   node;
    }

    void CELLTerrain::cancelRequest(CELLQuadTree* node)
    {
        char    szBuf[128];
        sprintf(
            szBuf
            , "%d-%d-%d:%p"
            , node->_tileId._lev
            , node->_tileId._row
            , node->_tileId._col
            , node);
        MapNode::iterator itr = _nodes.find(szBuf);
        if (itr != _nodes.end())
        {
            _nodes.erase(itr);
        }
    }

    void CELLTerrain::releaseTexture(uint texId)
    {
        _textureMgr.freeTexture(texId);
    }

    void CELLTerrain::onTaskCancel(CELLTask* task)
    {
        delete  task;
    }

    void CELLTerrain::onTaskExe(CELLTask* task)
    {
        CELLTileTask*   pTask   =   dynamic_cast<CELLTileTask*>(task);
        if (pTask == 0)
        {
            return;
        }
        char    szPathName[CELL_PATH_LENGHT];
        sprintf(szPathName, "%s/L%02d/%06d-%06d.jpg", _path, pTask->_tileId._lev + 1, pTask->_tileId._row, pTask->_tileId._col);
        if(CELLImageLoader::loadImage(szPathName, pTask->_image))
        {
            CELLMutex::ScopeLock lk(_mutex);
            _tasks.push_back(pTask);
        }
        else
        {
            delete  task;
        }
    }

    void CELLTerrain::onTaskFinish(CELLTask* task)
    {
    }

 

    void CELLTerrain::calcVertexBuffer(CELLQuadTree::ArrayNode& nodes, ArrayVertex& vertx)
    {
        vertx.resize(nodes.size() * 6);
        P3U3*   vPlane  =   &vertx.front();
        for (size_t i = 0 ;i < nodes.size() ; ++ i)
        {
            CELLQuadTree*   pNode   =   nodes[i];
            real2           vStart  =   pNode->_vStart;
            real2           vEnd    =   pNode->_vEnd;

            float2          uvStart =   pNode->_uvStart;
            float2          uvEnd   =   pNode->_uvEnd;
            vPlane[0].x     =   vStart.x;
            vPlane[0].y     =   0;
            vPlane[0].z     =   vEnd.y;

            vPlane[0].u     =   uvStart.x;
            vPlane[0].v     =   uvEnd.y;
            vPlane[0].w     =   pNode->_textureId;

            vPlane[1].x     =   vEnd.x;
            vPlane[1].y     =   0;
            vPlane[1].z     =   vEnd.y;

            vPlane[1].u     =   uvEnd.x;
            vPlane[1].v     =   uvEnd.y;
            vPlane[1].w     =   pNode->_textureId;

            vPlane[2].x     =   vEnd.x;
            vPlane[2].y     =   0;
            vPlane[2].z     =   vStart.y;
            vPlane[2].u     =   uvEnd.x;
            vPlane[2].v     =   uvStart.y;
            vPlane[2].w     =   pNode->_textureId;

            vPlane[3].x     =   vStart.x;
            vPlane[3].y     =   0;
            vPlane[3].z     =   vEnd.y;

            vPlane[3].u     =   uvStart.x;
            vPlane[3].v     =   uvEnd.y;
            vPlane[3].w     =   pNode->_textureId;

            vPlane[4].x     =   vEnd.x;
            vPlane[4].y     =   0;
            vPlane[4].z     =   vStart.y;
            vPlane[4].u     =   uvEnd.x;
            vPlane[4].v     =   uvStart.y;
            vPlane[4].w     =   pNode->_textureId;

            vPlane[5].x     =   vStart.x;
            vPlane[5].y     =   0;
            vPlane[5].z     =   vStart.y;

            vPlane[5].u     =   uvStart.x;
            vPlane[5].v     =   uvStart.y;
            vPlane[5].w     =   pNode->_textureId;

            vPlane          +=  6;
        }

    }

    void CELLTerrain::calcIndex(CELLQuadTree::ArrayNode& nodes)
    {
        _vertex.resize(nodes.size() * 4);
        _facees.resize(nodes.size() * 2);
        P3U3*   vPlane  =   &_vertex.front();
        for (size_t i = 0 ;i < nodes.size() ; ++ i)
        {
            CELLQuadTree*   pNode   =   nodes[i];
            real2           vStart  =   pNode->_vStart;
            real2           vEnd    =   pNode->_vEnd;

            float2          uvStart =   pNode->_uvStart;
            float2          uvEnd   =   pNode->_uvEnd;
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

            vPlane          +=  4;
            short   id      =   short(i) * 4;
            FaceIndex   index0  =   {id,id + 1,id + 2};
            FaceIndex   index1  =   {id,id + 2,id + 3};
            _facees[i*2 + 0]    =   index0;
            _facees[i*2 + 1]    =   index1;
        }
    }

}

