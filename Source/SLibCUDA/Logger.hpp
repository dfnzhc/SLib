/**
 * @File Logger.hpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2025/7/3
 * @Brief This file is part of SLib.
 */
 
#pragma once

// TODO: 用于在 CUDA 设备代码中进行打印的日志类型
// 想法：创建一个设备可访问的缓冲区，向缓冲区中写入日志。在 Host 中调用接口访问日志。
// 难点：如何进行日志字符串的规范化？