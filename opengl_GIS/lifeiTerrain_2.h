
#pragma once
#include "lifeiQuadTree.h"
#include "lifeiContext.h"
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
		typedef std::map<std::string, lifeiQuadTree*>	mapQuadTreeNode;
		typedef std::vector<P3U3>						arrayVertex;
		
	public:
		lifeiQuadTree*									_root;
		lifeiContext&									_context;
		lifeiTaskSystem_2								_taskSystem;
		arrayTask										_tasksLoaded;	//��������Ƭ�������������飬
		lifeiMutex_2									_mutex;
		mapQuadTreeNode									_quadTreeNodeSet;//��������Ƭ�������Ĳ�������
		arrayVertex										_vertexVector;
		lifeiTextureMgr_2								_textureMgr;
		lifeiCounts										_counts;
		
		IPluginTileManager*								_tileSourcePlugin;
		HMODULE											_hTileSourceDll;

	public:
		lifeiTerrain_2(lifeiContext& context);
		~lifeiTerrain_2();

		//���س���
		virtual bool loadScene(const char* fileName);
		//�����ڵ�
		virtual void initialize();
		//����Ҫ���Ƶ���Ƭ����
		virtual void update(lifeiContext& context);
		//����
		virtual void render(lifeiContext& context);
		//��ȡͳ����Ϣ
		virtual lifeiCounts& getCounts();
		//���Ʒ�ʽ1���������ݴ��
		virtual void renderPackVertex(lifeiContext& context);

	public:
		//���Ĳ����ڵ�node�����Լ���������Ƭ����ϵͳ����ȡ��Ӧ����Ƭ����
		virtual void request(lifeiQuadTree* node);
		///���Ĳ����ڵ�node�����Դ�������Ƭ����ϵͳ���Ƴ�
		virtual void cancelRequest(lifeiQuadTree* node);
		//�ͷ�����
		virtual void releaseTexture(unsigned int texId);

	public:
		//����ȡ��֪ͨ
		virtual void onTaskCancel(lifeiTask_2* task);
		//����ִ��֪ͨ
		virtual void onTaskExe(lifeiTask_2* task);
		//�������֪ͨ
		virtual void onTaskFinish(lifeiTask_2* task);

	protected:
		//�����Ĳ����ڵ㹹�������漯��
		void calcVertexBuffer(lifeiQuadTree::ArrayNode& nodes, arrayVertex& vertex);
		IPluginTileManager* createTileSourceDLL(const char* dllFileName);

	};
}