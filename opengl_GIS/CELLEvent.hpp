#pragma once
#include "CELLPlatform.hpp"
#include "CELLObject.hpp"

#if CELL_PLATFORM == CELL_PLATFORM_WIN32
namespace CELL
{
	class CELLEvent : public CELLObject
	{
	protected:
		HANDLE _handle;
	public:
		CELLEvent()
		{
			_handle = CreateEvent(0, 0, 0, 0);
		}
		virtual ~CELLEvent()
		{
			CloseHandle(_handle);
			_handle = 0;
		}
		bool set()
		{
			return SetEvent(_handle) == TRUE;
		}

		bool wait(DWORD ms = 0xFFFFFFFF)
		{
			switch (WaitForSingleObject(_handle, ms))
			{
			case WAIT_OBJECT_0:
				return true;
			case WAIT_TIMEOUT:
				return false;
			default:
				return false;
			}
		}

		void reset()
		{
			ResetEvent(_handle);
		}
	};
}
#endif