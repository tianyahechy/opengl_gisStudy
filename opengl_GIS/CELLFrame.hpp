#pragma once

#include    "lifeiContext.h"
#include    "CELLInput.hpp"
namespace   CELL
{

    class   CELLFrame :public CELLInput
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
		virtual void    onFrameStart(lifeiContext& context) = 0;

        /// <summary>
        /// 结束绘制
        /// </summary>
		virtual void    onFrameEnd(lifeiContext& context) = 0;
    };
}