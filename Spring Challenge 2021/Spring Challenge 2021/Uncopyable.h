#pragma once

class Uncopyable
{
protected:
	Uncopyable() {}
	~Uncopyable() {}

	// Prevent any class inheriting it from being copied.
	Uncopyable(Uncopyable const&) = delete;
	Uncopyable& operator=(Uncopyable const&) = delete;
};
