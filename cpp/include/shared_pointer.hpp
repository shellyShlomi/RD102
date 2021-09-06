#ifndef __ILRD_RD102_SHARED_POINTER_HPP__
#define __ILRD_RD102_SHARED_POINTER_HPP__

namespace ilrd
{

template <class T>
class SharedPointer
{

public:
    explicit inline SharedPointer(T *ptr_ = 0); 
    inline SharedPointer(const SharedPointer &other_);
    inline SharedPointer &operator=(const SharedPointer &other_);
    inline ~SharedPointer();

	inline T *GetCPointer() const;
	inline operator T*() const;
	inline T &operator*() const;
	inline T *operator->() const;

private:
	struct SharedData
	{
		size_t m_counter;
		T *m_data;
	};
	SharedData *m_data;

}; // SharedPointer

} // ilrd

#endif //__ILRD_RD102_SHARED_POINTER_HPP__
