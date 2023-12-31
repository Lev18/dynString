#include "dynStr.h"

#include <iostream>
#include <cstring>


MyString::MyString(const char* ptr) {
int size = strlen(ptr);
  if (size > m_smallStrSize) {
    optimString.newString = new dyn_str;
    optimString.newString->size = size;
    optimString.newString->arr = new char[optimString.newString->size];
    const char* pt = ptr;
    int i = 0;
    while (i < optimString.newString->size) {
       optimString.newString->arr[i] = *pt;
      ++pt;
      ++i;
    }
    m_isSmal = false;
  } else {
    m_isSmal = true;
    optimString.newString = nullptr;
    strncpy(optimString.string, ptr, sizeof(optimString.string));
    optimString.string[strlen(ptr)] = '\0';
  }
}

MyString::MyString(const std::string& str){
  if (str.length() > m_smallStrSize) { 
    optimString.newString = new dyn_str;
    optimString.newString->size = str.length();
    optimString.newString->arr = new char[str.length()];
    
    int i = 0;
    for (auto ch : str) {
     optimString.newString->arr [i] = ch;
      ++i;
    }
    m_isSmal = false;
  } else {
    m_isSmal = true;
    optimString.newString = nullptr;
    int i = 0;
    for (auto ch : str) {
     optimString.string[i] = ch;
      ++i;
    }
    optimString.string[i] = '\0';
  }
}

MyString::MyString(const MyString& oth) {

if (!oth.m_isSmal) { 
    optimString.newString = new dyn_str;
    optimString.newString->size = oth.optimString.newString->size;
    optimString.newString->arr = new char[oth.optimString.newString->size];
    
    for (int i = 0; i < oth.optimString.newString->size; ++i) {
     optimString.newString->arr [i] = oth.optimString.newString->arr[i];
    }
    m_isSmal = false;
  } else {
    m_isSmal = true;
    optimString.newString = nullptr;

    int smallSize = strlen(oth.optimString.string);
    for (int i = 0; i < smallSize; ++i) {
     optimString.string[i] = oth.optimString.string[i];
    }
    optimString.string[smallSize] = '\0';
  }
}

MyString::MyString(MyString&& lhs) {
  if (!lhs.m_isSmal) { 
    optimString.newString = std::move(lhs.optimString.newString);
    optimString.newString->size = std::move(lhs.optimString.newString->size);
    optimString.newString->arr = std::move(lhs.optimString.newString->arr); 
    lhs.optimString.newString->arr = nullptr;
    lhs.optimString.newString->size = 0;
    m_isSmal = false;
  } else {
      m_isSmal = true;
      optimString.newString = nullptr;

      std::strcpy(optimString.string, lhs.optimString.string);
  }
}

void MyString::set_size(int s) {
  optimString.newString->size = s;
}

MyString MyString::operator+=(const MyString& src) {
    if (!src.m_isSmal || !this->m_isSmal) {
      int newSize = this->optimString.newString->size + src.optimString.newString->size;
      char* tmp = new char[newSize];
      int i = 0;
      while (i < optimString.newString->size) {
        tmp[i] = optimString.newString->arr[i];
        ++i;
      }
      int j = 0;
      while (i < newSize) {
        tmp[i] = src.optimString.newString->arr[j];
        ++j;
        ++i;
      }
      
      delete[] optimString.newString->arr;
      optimString.newString->arr = tmp;
      optimString.newString->size = newSize;
      m_isSmal = false;

    } else {
      int strLen = strlen(src.optimString.string);
      int smallString = strlen(this->optimString.string); 
      int newStr = strLen + smallString;
      int i = 0;
      while (smallString < newStr) {
        optimString.string[smallString] = src.optimString.string[i];
        ++i;
        ++smallString;
      }
      optimString.string[newStr] = '\0';
    }
    return *this;
}

MyString MyString::operator+=(const char* src) {
    int srcSize = strlen(src);
    int newStrSize = strlen(optimString.string) + srcSize;
    if (srcSize > m_smallStrSize || newStrSize > 16) {
      optimString.newString = new dyn_str;
      char* tmp = new char[srcSize];
      int i = 0;
      while (i < optimString.newString->size) {
        tmp[i] = optimString.newString->arr[i];
        ++i;
      }
      int j = 0;
      while (j < srcSize) {
        tmp[i] = src[j];
        ++j;
        ++i;
      }
      tmp[newStrSize] = '\0';
      
      delete[] optimString.newString->arr;
      optimString.newString->arr = tmp;
      optimString.newString->size += srcSize;
      m_isSmal = false;
    } else {
      int smallString = strlen(optimString.string) ;
      int i = 0;
      while (smallString < newStrSize ) {
        optimString.string[smallString] = src[i];
        ++i;
        ++smallString;
      }
      optimString.string[newStrSize] = '\0';
    }
    return *this;
}

MyString MyString::operator+=(const char ch ) {
    
    if (!this->m_isSmal) {
      int newSize = optimString.newString->size + 1;
      char* tmp = new char[newSize];

      int i = 0;
      while (i < optimString.newString->size) {
        tmp[i] = optimString.newString->arr[i];
        ++i;
      }
      tmp[i] = ch;
      set_size(newSize);
      delete [] optimString.newString->arr;
      optimString.newString->arr = tmp;
    } else {
      strcat(optimString.string, &ch);
    }

  return *this;
}

void MyString::app(const MyString& src, char ch) {
    
  if (!src.m_isSmal) {
    int newSize = src.optimString.newString->size + 1;
    char* tmp = new char[newSize];

    int i = 0;
    while (i < src.optimString.newString->size) {
      tmp[i] = src.optimString.newString->arr[i];
      ++i;
    }

    tmp[i] = ch;
    set_size(newSize);
    delete [] src.optimString.newString->arr;
    src.optimString.newString->arr = tmp;

  } else {
      optimString.string[src.m_gettr] = ch;
    }
    
}

std::ostream& operator<< (std::ostream& ostr, const MyString& src) {
  const int m_smallStrSize = strlen(src.optimString.string);
  if (!src.m_isSmal || src.m_gettr > 16) {
    for (int i =  0; i < src.optimString.newString->size; ++i) {
      ostr << src.optimString.newString->arr[i];
    }
  } else {
    for (int i =  0; i <m_smallStrSize; ++i) {
      ostr << src.optimString.string[i];
    }
  }
  return ostr;
}

std::istream& operator>> (std::istream& istr, MyString& src) {
  char ch;
  if(!src.m_isSmal) {
    src.optimString.newString->size  = 0;
  }

  while(istr.get(ch)  && !std::isspace(ch)){
    src += ch;
    ++src.m_gettr;
  }
  return istr;
}

MyString::~MyString() {
  if(!m_isSmal){
    delete []  optimString.newString->arr;
    delete optimString.newString;
  }
}
