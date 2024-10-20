#pragma once

class INonCopyable
{
public:
	INonCopyable() = default;
	INonCopyable(const INonCopyable&) = delete;
	void operator=(const INonCopyable&) = delete;
};