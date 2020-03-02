#pragma once
#include "export.h"
#include "lifeiObject_2.h"

namespace CELL
{
	class lifeiEvent_2 : public lifeiObject_2
	{
	protected:
		HANDLE	_handle;

	public:
		lifeiEvent_2()
		{
			_handle = CreateEvent(0, 0, 0, 0);
		}

		virtual ~lifeiEvent_2()
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
				return true;
			}
		}

		void reset()
		{
			ResetEvent(_handle);
		}
	};
}
