#ifndef MYEXCPTION_H
#define MYEXCPTION_H


class MyExcption
{
public:
    MyExcption(const char *err);
    const char* what() throw(){
        return this->error;
    }
private:
    const char *error;
};

#endif // MYEXCPTION_H
