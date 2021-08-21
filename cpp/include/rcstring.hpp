#ifndef ILRD_RD102_RCSTRING_HPP
#define ILRD_RD102_RCSTRING_HPP

#include <iosfwd>

namespace ilrd
{

	class RCString
	{
	public:
		RCString(const char *cstr_ = ""); // non-explicit on purpose
		RCString(const RCString &other_);
		~RCString();
		RCString &operator=(const RCString &other_);
		size_t Length() const;
		const char *CStr() const;
		char &operator[](size_t index);
		char operator[](size_t index) const;

	private:
		typedef class RefCountStr RefCountStr_t;
		RefCountStr_t *m_data;
	}; //RCString

	std::ostream &operator<<(std::ostream &os, const RCString &str);
	std::istream &operator>>(std::istream &is, RCString &str);
	bool operator<(const RCString &str1, const RCString &str2);
	bool operator>(const RCString &str1, const RCString &str2);
	bool operator==(const RCString &str1, const RCString &str2);
	bool operator!=(const RCString &str1, const RCString &str2);

} //ilrd

#endif /* ILRD_RD102_RCSTRING_HPP */