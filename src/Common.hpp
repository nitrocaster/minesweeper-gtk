#ifndef COMMON_HPP
#define COMMON_HPP

struct Size
{
    int width, height;
	
    Size() : width(0), height(0)
    {
    }
	
    Size(int w, int h) : width(w), height(h)
    {
    }
	
    inline int area() const
    {
        return width*height;
    }
	
    inline bool operator==(const Size &that) const
    {
        return width == that.width && height == that.height;
    }
};

#endif
