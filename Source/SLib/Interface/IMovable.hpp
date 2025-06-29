/**
 * @File IMovable.hpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2025/6/29
 * @Brief This file is part of SLib.
 */

#pragma once

namespace slib {

class CMoveable
{
public:
    CMoveable()          = default;
    virtual ~CMoveable() = default;

    CMoveable(const CMoveable&)            = delete;
    CMoveable& operator=(const CMoveable&) = delete;

    CMoveable(CMoveable&&)            = default;
    CMoveable& operator=(CMoveable&&) = default;
};

} // namespace slib