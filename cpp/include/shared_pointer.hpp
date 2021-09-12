// Developer: Shelly Shlomi
// Status: Approved
// Reviewer: SHIR
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
		inline SharedPointer(T *ptr_ = 0);
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
		template <class U>
		friend class SharedPointer;

		T *m_data;
		size_t *m_counter;

		inline void SharedDataCleanUp();
		inline size_t *RefDec(size_t *m_counter);
		inline size_t *RefInc(size_t *m_counter);

		//to disallow heap alloction of SharedPointer
		void *operator new(size_t);
		void operator delete(void *);
		void *operator new[](size_t);
		void operator delete[](void *);

	}; // SharedPointer

	template <class T>
	SharedPointer<T>::SharedPointer(T *ptr_) : m_data(ptr_), m_counter(new size_t(SELF_COUNT))
	{
		; //empty
	}

	template <class T>
	SharedPointer<T>::SharedPointer(const SharedPointer &other_) : m_data(other_.m_data), m_counter(RefInc(other_.m_counter))
	{
		; //empty
	}

	template <class T>
	template <class U>
	SharedPointer<T>::SharedPointer(const SharedPointer<U> &other_) : m_data(other_.m_data), m_counter(RefInc(other_.m_counter))
	{
		; //empty
	}

	template <class T>
	SharedPointer<T> &SharedPointer<T>::operator=(const SharedPointer &other_)
	{
		RefInc(other_.m_counter);
		SharedDataCleanUp();
		m_data = other_.m_data;
		m_counter = other_.m_counter;

		return (*this);
	}

	template <class T>
	template <class U>
	SharedPointer<T> &SharedPointer<T>::operator=(const SharedPointer<U> &other_)
	{
		return (*this = SharedPointer<T>(other_));
	}

	template <class T>
	SharedPointer<T>::~SharedPointer()
	{
		SharedDataCleanUp();
	}

	template <class T>
	T *SharedPointer<T>::GetPtr() const
	{
		return (m_data);
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
	void SharedPointer<T>::SharedDataCleanUp()
	{

		RefDec(m_counter);

		if (NOT_EXSIST == *m_counter)
		{
			delete (m_data);
			m_data = NOT_EXSIST;
			*m_counter = NOT_EXSIST;
			delete (m_counter);
			m_counter = NOT_EXSIST;
		}

		return;
	}

	template <class T>
	inline size_t *SharedPointer<T>::RefDec(size_t *m_counter)
	{
		(*m_counter) -= 1;
		return (m_counter);
	}

	template <class T>
	inline size_t *SharedPointer<T>::RefInc(size_t *m_counter)
	{
		(*m_counter) += 1;
		return (m_counter);
	}

} // ilrd

#endif //__ILRD_RD102_SHARED_POINTER_HPP__
