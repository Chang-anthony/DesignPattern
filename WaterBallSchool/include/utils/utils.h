#pragma once
#ifndef _UTILS_H_
#define _UTILS_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <codecvt>
#include <locale>


class CustomException : public std::exception{
public:
    CustomException(const std::wstring message) 
        :msg(ConvertToString(message))
    {
        // auto convert_tostring = [](const std::wstring& input)
        // {
        //     std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		//     return converter.to_bytes(input);
        // };
        // msg = convert_tostring(message);
    }

    const std::string what()
    {
        return msg;
    }

private:
    // convert string to wstring
	inline std::wstring ConvertToWstring(const std::string& input)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.from_bytes(input);
	}
	// convert wstring to string 
	inline std::string ConvertToString(const std::wstring& input)
	{
		//std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.to_bytes(input);
	}

    std::string msg;
};

class utils 
{
private:
    /* data */
public:
    utils(/* args */){};
    ~utils(){};

    template<typename T>
    static T* RequireNonNull(T* object)
    {
        if(object == nullptr)
            throw std::invalid_argument("object can't be null.");
        return object;
    }

    template<typename T>
    static void ShouldBePositive(T val)
    {
        if(val <= 0)
            throw std::invalid_argument("val must be positive.");
    }

    static void LengthShouldBe(std::string str,int min,int max)
    {
        if(str.size() > max || str.size() < min)
        {
            std::ostringstream oss;//   透過 ostringstream 來建立一個整數字符串
            oss << str <<" size" << " should be " << min << " ~ " << max << ".";
            throw std::invalid_argument(oss.str());
        }
    }

    static void LengthShouldBe(std::wstring str,int min,int max)
    {
        if(str.size() > max || str.size() < min)
        {
            std::wostringstream woss;//   透過 ostringstream 來建立一個整數字符串
            woss << str << L" size" << L" should be " << min << L" ~ " << max << L".";
            // const wchar_t* foo = woss.str().c_str();
            CustomException except = CustomException(woss.str());
            throw std::invalid_argument(except.what());
            
            //std::wcout << str << std::endl;
            //std::wcout << except.what() << std::endl;
            //throw except.what();
            //throw except;
        } 
    }

    template<typename T>
    static void ValShouldBigger(T val,int min)
    {
        if(val < min)
        {
            std::ostringstream oss;//透過 ostringstream 來建立一個整數字符串
            oss << "val " << " should bigger than " << min << ".";
            throw std::invalid_argument(oss.str());
        }
    }

    template<typename T>
    static void SizeShouldBigger(const std::vector<T>& arr,int val)
    {
        if(arr.size() < val)
            throw std::invalid_argument("arr size should bigger than val");
    }

    template<typename T>
    static void ArrayShouldNotBeEmpty(const std::vector<T>& arr)
    {
        if(arr.empty())
            throw std::invalid_argument("arr can't be empty");
    }

    template<typename T>
    static std::string ToString(const T& val)
    {
        auto convert = [](const T& val)
        {
            std::ostringstream oss;
            oss << val;
            return oss.str();
        };
        return convert(val);
    }

    template<typename T>
    static std::string ToString(const std::vector<T>& arr)
    {
        auto convert = [](const T& val)
        {
            std::ostringstream oss;
            oss << val;
            return oss.str();
        };
        
        std::string result = "[";
        for(const T& element : arr)
            result += convert(element) + " , ";
        if(!arr.empty())
            result = result.substr(0,result.size() - 3);//移除最後兩個空格與逗號
        result += "]";
        return result;
    }

};

#endif