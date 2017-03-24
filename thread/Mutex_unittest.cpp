#include "Mutex.h"

int main(int argc, char **argv){
	liangsc::MutexLock mutex_;
	liangsc::MutexLockGuard lock(mutex_);
	return 0;
}