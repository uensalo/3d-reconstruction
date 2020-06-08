#pragma once
#ifndef __recon_random_h__
#define __recon_random_h__
#include "pcg/pcg32.hpp"
namespace recon {
	class Random {
	public:
		static float next() {
			return rng.nextFloat();
		}

		static int next_int(int a, int b) {
			return (int)rng.nextFloat() * (b - a) + a;
		}

	private:
		static pcg32 rng;
		Random() {};
	};
}


#endif