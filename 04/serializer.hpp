#pragma once
#include <iostream>

enum class Error
{
    NoError,
    CorruptedArchive
};

class Serializer
{
    static constexpr char Separator = ' ';
public:
    explicit Serializer(std::ostream& out)
        : out_(out)
    {
    }

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... Args>
    Error operator()(Args &&... args) {
        return process(std::forward<Args>(args)...);
    }
    
private:
    std::ostream &out_;
    // process использует variadic templates
    Error save(bool &val) {
        if(val){
            out_ << "true" << Separator;
        }else{
            out_ << "false" << Separator;
        }
        return Error::NoError;
    }

    Error save(uint64_t &val) {
        out_ << val << Separator;
        return Error::NoError;
    }
    Error process() 
    {
        return Error::NoError;
    }

    template<class T, class... Args>
    Error process(T &&val, Args &&... args) {
        Error er = save(val);
        if(er == Error::NoError){
            return process(std::forward<Args>(args)...);
        }
        return Error::CorruptedArchive;
    }
};
class Deserializer {
    
public:
    explicit Deserializer(std::istream &in)
            : in_(in) {
    }

    template<class T>
    Error load(T &object) {
        return object.serialize(*this);
    }

    template<class... Args>
    Error operator()(Args &&... args) {
        return process(std::forward<Args>(args)...);
    }

private:
    std::istream &in_;
    Error load1(bool &v) {
        std::string text;
        in_ >> text;

        if (text == "true"){
            v = true;
            return Error::NoError;
        } else if (text == "false"){
            v = false;
            return Error::NoError;
        } else{
            return Error::CorruptedArchive;
        }
    }
    Error load1(uint64_t &v) {
        std::string text;
        in_ >> text;
        if(text.size()){
            v = stoul(text);
            return Error::NoError;
        } else{
            return Error::CorruptedArchive;
        }
    }
    Error process() 
    {
        return Error::NoError;
    }
    template<class T, class... Args>
    Error process(T &&val, Args &&... args) {
        Error er = load1(val);
        if(er == Error::NoError){
            return process(std::forward<Args>(args)...);
        }
        return Error::CorruptedArchive;
    }
};