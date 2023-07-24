#ifndef dLibAsistExecHxx
#define dLibAsistExecHxx
//headers
#include "fMemo.hxx"
#include <thread>
#include <future>
#include <atomic>
#include <mutex>
//content
namespace nLibAsist
{
namespace nExec
{
/* tAtomic
 * type of atomic value wrapper
 */
template<typename tT>
using tAtomic = std::atomic<tT>;
//typedef
/* tLocker
 * type of mutex wrapper
 */
dTypeDefIline class tLocker
{
public://typedef

	using tThis = tLocker;

	using tOpened = tAtomic<nBool::tFlag>;
	using tHandle = std::mutex;

public://codetor

	tLocker(): vOpened{1}, vHandle{}
	{
	}

	tLocker(const tThis &rCopy) = delete;
	tLocker(tThis &&rCopy)		= delete;

	~tLocker() = default;

public://actions

	aHasReturned("returns true if it was on opened state"
	) dFuncDefIline tOpened fLock()
	{
		if(this->vOpened)
		{
			this->vHandle.lock();
			this->vOpened = 0;
			return 1;
		}
		else
		{
			return 0;
		}
	}//fLock
	aHasReturned("returns true if it was on locked state"
	) dFuncDefIline auto fOpen()
	{
		if(this->vOpened)
		{
			return 0;
		}
		else
		{
			this->vOpened = 1;
			this->vHandle.unlock();
			return 1;
		}
	}//fOpen

public://operats

	aUseReturned("conversion from locker to it's underlying handle type"
	) dFuncDefIline
	operator auto &()
	{
		return this->vHandle;
	}//operator tHandle(tLocker)
	aUseReturned("conversion from locker to it's underlying const handle type"
	) dFuncDefIline
	operator auto &() const
	{
		return this->vHandle;
	}//operator tHandle(tLocker) const

	void operator=(const tThis &rCopy) = delete;
	void operator=(tThis &&rCopy)	   = delete;

private://datadef

	tOpened vOpened;//flag for the locked/opened state
	tHandle vHandle;//the internal heavy-lifting object

};//tLocker
/* tLockerGuard
 * automatic scoped lock-open caller
 */
using tLockerGuard = std::lock_guard<tLocker::tHandle>;
/* tLockerScope
 * automatic scoped lock-open caller
 */
using tLockerScope = std::scoped_lock<tLocker::tHandle>;
template<typename tT>
/* tSetter
 * type of promise wrapper
 */
using tSetter = std::promise<tT>;
template<typename tT>
/* tGetter
 * type of future wrapper
 */
using tGetter = std::future<tT>;
/* tGetter
 * type of promisified callback
 */
template<typename... tT>
using tTask = std::packaged_task<tT...>;
/* tFlow
 * type of program execution thread
 */
using tFlow		 = std::thread;
using tFlowIdent = std::thread::id;//internal identifier
using tFlowIndex = nNums::tSizeM;  //numeric index
//getters
aUseReturned("get internal identifier of the current thread"
) dFuncDefIline tFlowIdent fGetFlowIdent()
{
	return std::this_thread::get_id();
}//fGetFlowIdent
//getters
aUseReturned("get numeric index of the current thread"
) dFuncDefIline tFlowIndex fGetFlowIndex()
{
	tFlowIdent vFlowIdent = fGetFlowIdent();
	return std::hash<tFlowIdent>{}(vFlowIdent);
}//fGetFlowIdent
//actions
template<typename tFuncT, typename... tArgsT>
aUseReturned("call function with arguments right now"
) dFuncDefIline auto fCallAsync(tFuncT vFuncT, tArgsT &&...vArgsT)
{
	return std::async(
		std::launch::async,
		std::forward<tFuncT>(vFuncT),
		std::forward<tArgsT>(vArgsT)...
	);
}//fCallAsync
template<typename tFuncT, typename... tArgsT>
aUseReturned("call function with arguments when the returned value is requested"
) dFuncDefIline auto fCallDefer(tFuncT vFuncT, tArgsT &&...vArgsT)
{
	return std::async(
		std::launch::deferred,
		std::forward<tFuncT>(vFuncT),
		std::forward<tArgsT>(vArgsT)...
	);
}//fCallDefer
//operats
}//namespace nExec
}//namespace nLibAsist
#endif//dLibAsistExecHxx
