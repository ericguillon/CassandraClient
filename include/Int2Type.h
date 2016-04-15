#ifndef INT2TYPE_H
#define INT2TYPE_H

template <int integer>
class Int2Type
{
public:
    enum
    {
        value = integer
    };
};

#endif // INT2TYPE_H
