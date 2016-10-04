# cpp-itertools
Creating Python-style iteration tools (ala itertools) for C++11

This code shows off a few things:
- Creating a zip() and enumerate() iteration adaptors akin to Python itertools utilities of the same name.
- Creating an adaptor for a container class which doesn't support the new C++11 range-for syntax. This can be used to adapt an older style class to the new C++11 range-for syntax. We have to take special care to make it compatible with both the C++11 range-based for syntax and the zip() and enumerate() adaptors above.
