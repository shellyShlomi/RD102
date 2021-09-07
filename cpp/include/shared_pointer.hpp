// Developer: Shelly Shlomi
// Status: in development
// Reviewer: SIRE
// Group: RD102
// date: 06.09.21
// description: SharedPointer with referenc counting

#ifndef __ILRD_RD102_SHARED_POINTER_HPP__
#define __ILRD_RD102_SHARED_POINTER_HPP__

#include <cstddef>

namespace ilrd
{
	static const size_t SELF_COUNT(1);
	static const size_t NOT_EXSIST(0);

	template <class T>
	class SharedPointer
	{

	public:
		explicit inline SharedPointer(T *ptr_ = 0);
		inline SharedPointer(const SharedPointer &other_);
		template <class U>
		inline SharedPointer(const SharedPointer<U> &other_);
		inline SharedPointer &operator=(const SharedPointer &other_);
		template <class U>
		inline SharedPointer &operator=(const SharedPointer<U> &other_);
		inline ~SharedPointer();

		inline T *GetPtr() const;
		inline T &operator*() const;
		inline T *operator->() const;

	private:
		struct SharedData
		{
			size_t m_counter;
			T *m_data;
		};

		SharedData *m_shared;

		inline SharedData *InitSharedData(T *ptr);
		inline void SharedDataCleanUp(SharedData *m_shared);
		inline void RefDec(SharedData *m_counter);
		inline void RefInc(SharedData *m_counter);

		template <class U>
		friend class SharedPointer;

	}; // SharedPointer
	template <class T, class U>
	void TestCast(T *test_to_cast, U *to_cast);

	template <class T>
	SharedPointer<T>::SharedPointer(T *ptr_) : m_shared(InitSharedData(ptr_))
	{
		; //empty
	}

	template <class T>
	SharedPointer<T>::SharedPointer(const SharedPointer &other_) : m_shared(other_.m_shared)
	{
		RefInc(m_shared);
	}

	template <class T>
	template <class U>
	SharedPointer<T>::SharedPointer(const SharedPointer<U> &other_) : m_shared(reinterpret_cast<SharedData *>(other_.m_shared))
	{

		TestCast(GetPtr(), other_.GetPtr());
		RefInc(m_shared);
	}

	template <class T>
	SharedPointer<T> &SharedPointer<T>::operator=(const SharedPointer &other_)
	{

		RefInc(other_.m_shared);
		SharedDataCleanUp(m_shared);
		m_shared = other_.m_shared;

		return (*this);
	}

	template <class T>
	template <class U>
	SharedPointer<T> &SharedPointer<T>::operator=(const SharedPointer<U> &other_)
	{
		TestCast(GetPtr(), other_.GetPtr());

		SharedPointer<T> cpy_O(other_); //++other_counter
		SharedDataCleanUp(m_shared);
		m_shared = cpy_O.m_shared;
		RefInc(m_shared);

		return (*this);
	}

	template <class T>
	SharedPointer<T>::~SharedPointer()
	{
		SharedDataCleanUp(m_shared);
	}

	template <class T>
	T *SharedPointer<T>::GetPtr() const
	{
		return (m_shared->m_data);
	}

	template <class T>
	T &SharedPointer<T>::operator*() const
	{
		return (*(GetPtr()));
	}

	template <class T>
	T *SharedPointer<T>::operator->() const
	{
		return (GetPtr());
	}

	template <class T>
	typename SharedPointer<T>::SharedData *SharedPointer<T>::InitSharedData(T *ptr)
	{
		SharedData *shared_ptr =
			static_cast<SharedData *>(::operator new(sizeof(SharedData)));

		shared_ptr->m_counter = SELF_COUNT;
		shared_ptr->m_data = ptr;

		return (shared_ptr);
	}

	template <class T>
	void SharedPointer<T>::SharedDataCleanUp(SharedData *m_shared)
	{

		RefDec(m_shared);

		if (NOT_EXSIST == m_shared->m_counter)
		{
			delete (m_shared->m_data);
			m_shared->m_data = 0;
			m_shared->m_counter = SELF_COUNT;
			delete (m_shared);
			m_shared = 0;
		}

		return;
	}

	template <class T, class U>
	void TestCast(T *test_to_cast, U *to_cast)
	{
		(void)test_to_cast;

		T *test_cast = to_cast;
		(void)test_cast;

		return;
	}

	template <class T>
	inline void SharedPointer<T>::RefDec(SharedData *m_shared)
	{
		--m_shared->m_counter;
	}

	template <class T>
	inline void SharedPointer<T>::RefInc(SharedData *m_shared)
	{
		++m_shared->m_counter;
	}

} // ilrd

#endif //__ILRD_RD102_SHARED_POINTER_HPP__
