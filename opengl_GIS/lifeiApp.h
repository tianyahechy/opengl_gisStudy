#pragma once

#include "lifeiPlatform.h"
#include "CELLFrame.hpp"

namespace CELL
{
	class LifeiApp
	{
	public:
		//�������ں���
		virtual bool createWindow(int width, int height, INSTANCE hInst) = 0;
		//�������
		virtual CELLFrame* createFrame() = 0;
		//��ں���
		virtual void main(int argc, char** argv) = 0;
	};
}