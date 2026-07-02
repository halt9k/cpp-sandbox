#include <sstream>

#include "hr_extended.h"
#include "sandbox_adapter.h"

#include <cstdio>
#include <iostream>
#include <string>

template <typename T> std::string to_str(const T& t)
	{
	std::ostringstream ss;
	ss << t;
	return ss.str();
	}

template <typename T> std::string to_str(const T& t);


void embedded_test_2(bool hood_is_working, int kitchen_pressure, int hood_pressure, int counter)
	{
	static float dp = 0;
	static int hood_speed_frequency = 100;
	if (hood_is_working)
		{
		dp += (kitchen_pressure - hood_pressure) * 0.2;
		if (counter % 5 == 0)
			{
			// DP&lt;=5 по модулю меньше 5
			if (std::abs(dp) > 5)
				{
				hood_speed_frequency += dp;
				dp = 0;
				}

			// if (hood_pressure >= kitchen_pressure - 2 && hood_pressure <= kitchen_pressure + 2) {}
			// else if (hood_pressure > kitchen_pressure + 2)  hood_speed_frequency -= 10;
			// else if (hood_pressure < kitchen_pressure - 2)  hood_speed_frequency += 10;

			if (hood_speed_frequency >= 40 && hood_speed_frequency <= 200) {}
			else if (hood_speed_frequency > 200)  hood_speed_frequency = 200;
			else if (hood_speed_frequency < 40)  hood_speed_frequency = 40;
			// ledcWrite(pwm_recirc_flap_ledChannel, hood_speed_frequency);
			}
		}
	else
		{
		dp = 0;
		hood_speed_frequency = 100;
		// ledcWrite(pwm_recirc_flap_ledChannel, hood_speed_frequency);

		hood_is_working = true;
		}
	cout << "hf:  " << hood_speed_frequency << " kp:   " << kitchen_pressure << " hp: " << hood_pressure << " dp: " << dp << endl;
	}

void embedded_test()
	{
	// VStrs lines = FIO::cin_read_lines();

	bool service_pin_unlocked = true;
	auto test = ("pin_unlocked.val=" + to_str<int>(service_pin_unlocked)).c_str();
	cout << test;
	float dp = -67 ;


	if (dp > 5.0f)
		dp = 5.0f;
	if (dp < -5.0f)
		dp = -5.0f;

	for (int i = 0; i < 300; i++)
		{
		auto kp = i < 100 ? 120 : 100;
		embedded_test_2(true, kp, 113, kp);
		}

	

	// VInts inputs = Vec::strs_to_ints(Str::split(lines[0]));
	// int N = inputs[0];
	// int Q = inputs[1];

	// cout << N << Q << endl;
	}


int main()
	{
	embedded_test();
	return 0;
	}