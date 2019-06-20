#pragma once

#include    "CELLContext.hpp"
#include    "CELLInput.hpp"
namespace   CELL
{

    class   CELLFrame :public CELLInput
    {
    public:
        CELLContext&    _context;
    public:
        CELLFrame(CELLContext& context)
            :_context(context)
        {}
        virtual ~CELLFrame()
        {}
        /// <summary>
        /// 更新数据
        /// </summary>
        virtual void    update(CELLContext& context) = 0;
        /// <summary>
        /// 开始绘制
        /// </summary>
        virtual void    onFrameStart(CELLContext& context)  =   0;

        /// <summary>
        /// 结束绘制
        /// </summary>
        virtual void    onFrameEnd(CELLContext& context)  =   0;
    };
}