#pragma once
#include <stdarg.h>
#include <stddef.h>

namespace eon {
namespace core {
    class Log {
    public:
        enum {
            TAB_NR_SPACES = 4
        };
        
        static Log* get(); // = 0
        virtual ~Log() {};
        void error(const char* format, ...);
        void info(const char* format, ...);
        void warning(const char* format, ...);

    protected:
        virtual void prepare_error();
        virtual void prepare_info();
        virtual void prepare_warning();
        virtual void print(char ch) = 0;
        virtual void print(const char* string) = 0;

    private:
        void print(unsigned int integer, size_t base);
        void print(const char* format, va_list arguments);
    };
}}
