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


void sendCommand(const char* str)
	{
	cout << "ok";
	}


void embedded_test()
	{
	bool start_button = true;

	// TODO 1 test
	bool hood_is_working = true;

	int fan_mode_auto = 2;
	fan_mode_auto = fan_mode_auto == 1 ? 0 : 1;
	fan_mode_auto = fan_mode_auto == 1 ? 0 : 1;

	float test1 = 0.0f;
	test1++;
	test1--;

	auto test = to_str<int>(0.6f * 0.9f / (test1));

	// TODO 1 test
	sendCommand("vis system_status,0");
	// Статус системы (system_status)
	if (start_button)
		{
		sendCommand("status_button.val=1");
		sendCommand("status_button.txt=\"\r\r\rВкл\"");
		}
	else
		{
		sendCommand("status_button.val=0");
		sendCommand("status_button.txt=\"\r\r\rВыкл\"");
		}

	auto send_command_str = [&](std::string cmd) {
		sendCommand(cmd.c_str());
		};
	// 45056, dark red
	std::string hood_col = hood_is_working ? "45056" : "0";
	send_command_str("pow_out.pco=" + hood_col);
	send_command_str("b_mode1.borderc=" + hood_col);
	send_command_str("b_mode2.borderc=" + hood_col);
	send_command_str("b_mode3.borderc=" + hood_col);

	// TODO 1 remove after test
	// int fan_mode_auto = 2;

	// 9810 = 0x21ca94, teal
	std::string btn_color = fan_mode_auto == 1 ? "9810" : "65535";
	send_command_str("b_mode1.pco=" + btn_color);
	btn_color = fan_mode_auto == 2 ? "9810" : "65535";
	send_command_str("b_mode2.pco=" + btn_color);
	btn_color = fan_mode_auto == 3 ? "9810" : "65535";
	send_command_str("b_mode3.pco=" + btn_color);
	}


int main()
	{
	embedded_test();
	return 0;
	}