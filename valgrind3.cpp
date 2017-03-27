#include <iostream>
#include <stdexcept>
#include <memory>

using namespace std;

class MyLogicError : public std::logic_error{
public:
	explicit MyLogicError(const string& what_arg)
		: std::logic_error(what_arg)
	{};
	explicit MyLogicError(const char* what_arg)
		: std::logic_error(what_arg)
	{};


};


class Resource
{ 
public:
    void use(const char* N)
    {
        cout << "Using resource. Passed " << *N << endl;
        if (*N == 'd')
        {
            throw MyLogicError("Passed d. d is prohibited.");
        }
    };
};



int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        cerr << "You need to pass 1 argument" << endl;
        exit(-1);
    }
    const char* N = argv[1];
    std::unique_ptr<Resource> rsc = nullptr;
    try
    {
        rsc = std::make_unique<Resource>();
        rsc->use(N);
    }
    catch (MyLogicError & e)
    {
        cout << e.what() << endl;
    }

    return 0;
}

