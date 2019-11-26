#pragma once

#include    "lifeiContext.h"
#include "lifeiInput.h"
namespace   CELL
{

    class   CELLFrame :public lifeiInput
    {
    public:
		lifeiContext&    _context;
    public:
        CELLFrame(lifeiContext& context)
            :_context(context)
        {}
        virtual ~CELLFrame()
        {}
        /// <summary>
        /// 更新数据
        /// </summary>
        virtual void    update(lifeiContext& context) = 0;
        /// <summary>
        /// 开始绘制
        /// </summary>
        virtual void    onFrameStart(lifeiContext& context)  =   0;

        /// <summary>
        /// 结束绘制
        /// </summary>
        virtual void    onFrameEnd(lifeiContext& context)  =   0;
    };
}