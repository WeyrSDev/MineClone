#pragma once

class Singleton {
public:
	//Make no copyable
	Singleton(Singleton&) = delete;
	Singleton& operator=(Singleton&) = delete;
	//Make no movable
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;
	
	Singleton() = default;
};
