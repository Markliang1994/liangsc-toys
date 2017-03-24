#include <pthread.h>

namespace liangsc{
	class MutexLock{
	public:
		MutexLock():
		lock_(PTHREAD_MUTEX_INITIALIZER){
		}
		void lock(){
			pthread_mutex_lock(&lock_);
		}
		void unlock(){
			pthread_mutex_unlock(&lock_);
		}
		~MutexLock(){ }
	private:
		pthread_mutex_t lock_;
	};

	class MutexLockGuard{
	public:
		MutexLockGuard(MutexLock &mutex):
		mutex_(mutex){
			mutex_.lock();
		}
		~MutexLockGuard(){
			mutex_.unlock();
		}
	private:
		MutexLock &mutex_;
	};

#define MutexLockGuard(x) error : "missing guard object";
}