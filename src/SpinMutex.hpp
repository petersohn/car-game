#ifndef SPINMUTEX_HPP_
#define SPINMUTEX_HPP_

#include <atomic>

namespace car {

class SpinMutex {
public:
	void lock() {
		while (flag.test_and_set(std::memory_order_acquire));
	}

	bool try_lock() {
		return flag.test_and_set(std::memory_order_acquire);
	}

	void unlock() {
		flag.clear(std::memory_order_release);
	}
private:
	std::atomic_flag flag = ATOMIC_FLAG_INIT;
};

}


#endif /* SPINMUTEX_HPP_ */
