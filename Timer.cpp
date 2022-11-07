#include "Timer.h"


LTimer::LTimer()
{
	//Initialize the variables: Khởi tạo các biến
	mStartTicks = 0;
	mPausedTicks = 0;
	mPaused = false;
	mStarted = false;
}
void LTimer::start()
{
	//Start the timer: Bắt đầu hẹn giờ
	mStarted = true;

	//Unpause the timer: Bỏ tạm dừng bộ hẹn giờ
	mPaused = false;

	//Get the current clock time: Nhận thời gian đồng hồ hiện tại
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void LTimer::stop()
{
	//Stop the timer: Dừng hẹn giờ
	mStarted = false;

	//Unpause the timer: Bỏ tạm dừng bộ hẹn giờ
	mPaused = false;

	//Clear tick variables: Xóa các biến đánh dấu
	mStartTicks = 0;
	mPausedTicks = 0;
}

void LTimer::pause()
{
	//If the timer is running and isn't already paused: Nếu bộ hẹn giờ đang chạy và chưa bị tạm dừng
	if (mStarted && !mPaused)
	{
		//Pause the timer: Dừng thời gian
		mPaused = true;

		//Calculate the paused ticks: Tính số tick bị tạm dừng
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

Uint32 LTimer::getTicks()
{
	//The actual timer time: Thời gian hẹn giờ thực tế
	Uint32 time = 0;

	//If the timer is running: Nếu bộ hẹn giờ đang chạy
	if (mStarted)
	{
		//If the timer is paused: Nếu bộ hẹn giờ đang dừng
		if (mPaused)
		{
			//Return the number of ticks when the timer was paused: Trả lại số lần đánh dấu khi bộ hẹn giờ bị tạm dừng
			time = mPausedTicks;
		}
		else
		{
			//Return the current time minus the start time: Trả lại thời gian hiện tại trừ đi thời gian bắt đầu
			time = SDL_GetTicks() - mStartTicks;
		}
	}

	return time;
}

bool LTimer::isStarted()
{
	//Timer is running and paused or unpaused: Bộ hẹn giờ đang chạy và bị tạm dừng hoặc bỏ tạm dừng
	return mStarted;
}

bool LTimer::isPaused()
{
	//Timer is running and paused: Bộ hẹn giờ đang chạy và bị tạm dừng
	return mPaused && mStarted;
}
