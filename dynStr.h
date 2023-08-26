#ifndef DYN_STR_H
#define DYN_STR_H
#include <string>

class MyString {
private:
  const int m_smallStrSize = 16;
  bool m_isSmal {false};
  int m_gettr {0};

  struct dyn_str {
    int size {0};
    char* arr  {nullptr};
  };

  union {
    char string [16];
    dyn_str* newString;
  }optimString;
  
public:
  MyString();
  ~MyString();
  MyString(const std::string& std);
  MyString(const char* str);
  MyString(const MyString& oth);
  MyString(const MyString&&) = delete;
  void set_size(int s);
  MyString operator+=(const MyString& src);  
  void app(const MyString& src, char ch) ;
  MyString operator=(const char* str);
  MyString operator+=(const char* str);
  MyString operator+=(const char sym);
  MyString operator+ (const MyString& src1);
  friend std::ostream& operator<< (std::ostream& ostr, const MyString& src);
  friend std::istream& operator>> (std::istream& input, MyString& src);

};

#endif

