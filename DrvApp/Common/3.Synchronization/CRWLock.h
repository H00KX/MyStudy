#pragma once
namespace ddk::lock
{
	class CRWLock
	{
	private:
		PERESOURCE res;
		NTSTATUS res_ns;
	public:
		CRWLock()
		{
			res = nullptr;
			res = reinterpret_cast<PERESOURCE>(malloc(PAGE_SIZE));
			NT_ASSERT(res != nullptr);
			NT_ASSERT(KeGetCurrentIrql() <= DISPATCH_LEVEL);
			res_ns = ExInitializeResourceLite(res);
		}
		~CRWLock()
		{
			NT_ASSERT(res != nullptr);
			NT_ASSERT(res_ns == STATUS_SUCCESS);
			ExDeleteResourceLite(res);
			free(res);
		}
		void lock_for_read()
		{
			NT_ASSERT(res != nullptr);
			NT_ASSERT(res_ns == STATUS_SUCCESS);
			NT_ASSERT(KeGetCurrentIrql() <= APC_LEVEL);
			ExEnterCriticalRegionAndAcquireResourceShared(res);
		}
		void lock_for_write()
		{
			NT_ASSERT(res != nullptr);
			NT_ASSERT(res_ns == STATUS_SUCCESS);
			NT_ASSERT(KeGetCurrentIrql() <= APC_LEVEL);
			ExEnterCriticalRegionAndAcquireResourceExclusive(res);
		}
		void unlock()
		{
			NT_ASSERT(res != nullptr);
			NT_ASSERT(res_ns == STATUS_SUCCESS);
			ExReleaseResourceAndLeaveCriticalRegion(res);
		}
	};
};