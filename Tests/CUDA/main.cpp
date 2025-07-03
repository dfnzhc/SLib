/**
 * @File main.cpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2025/7/3
 * @Brief This file is part of SLib.
 */

#include "CuTests.hpp"
#include <iostream>

int main()
{
    std::cout << "=================测试开始==================" << std::endl;
    if (int cnt = TestCommon()) {
        std::cout << "Common 测试有: '" << cnt << "' 个错误。" << std::endl;
    }
    
    std::cout << "=================测试结束==================" << std::endl;
}