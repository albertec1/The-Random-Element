#pragma once

#include "p2Defs.h"

class PerfTimer
{
public:

	PerfTimer();

	void Start();
	double ReadMs();
	uint64 ReadTicks();

private:
	uint64 started_at;
	static uint64 frequency;

};