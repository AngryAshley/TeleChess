#ifndef IREFEREE_H
#define IREFEREE_H

#include <string>

class IReferee
{
public:
    virtual bool CheckMove(std::string move) = 0;
    virtual ~IReferee() {}
};

class MReferee : public IReferee
{
public:
    bool CheckMove(std::string move)
    {
        return true;
    }
};

#endif