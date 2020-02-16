#pragma once
#include "lifeiPlatform.h"
#include "lifeiObject_2.h"

namespace CELL
{
	class lifeiEvent : public lifeiObject_2
	{
	protected:
		HANDLE _handle;
	public:
		lifeiEvent()
		{
			_handle = CreateEvent(0, 0, 0, 0);
		}
		virtual ~lifeiEvent()
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