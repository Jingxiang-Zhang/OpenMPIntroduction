#pragma once
#include <Windows.h>
#include <random>
#include <chrono>

inline void random_sleep()
{
	std::mt19937_64 rng;
	rng.seed(std::chrono::system_clock::now().time_since_epoch().count());
	int time = (int)std::uniform_real_distribution<double>(0, 5000)(rng);
	Sleep(time);
}