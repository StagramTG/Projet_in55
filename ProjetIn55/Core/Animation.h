#ifndef ANIMATION_H
#define ANIMATION_H

#include <glm/glm.hpp>
#include <string>

namespace IN
{
	static float TimeToFrame(float time)
	{
		float frame = 0.041666666667f;
		return time / frame;
	}

	static glm::vec2 FramesToTime(glm::vec2 frames)
	{
		float frame = 0.041666666667f;
		return frames * frame;
	}

	class Animation
	{
	private:
		std::string name;
		float start_time; //The start time of the animation (in seconds)
		float end_time;   //The end time of the animation (in seconds)
		int priority;   //The priority of this animation

	public:
		Animation()
		{
			start_time = 0;
			end_time = 0;
			priority = 0;
		}

		Animation(std::string in_name, glm::vec2 times, int in_priority)
		{
			name = in_name;
			start_time = times.x;
			end_time = times.y;
			priority = in_priority;
		}

		int GetPriority()
		{
			return priority;
		}

		float GetStartTime()
		{
			return start_time;
		}

		float GetEndTime()
		{
			return end_time;
		}
	};
}
#endif