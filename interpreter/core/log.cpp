#include <sys/types.h>
#include "log.h"
#include "system.h"

#define NUMERIC_BASE_CONVERSION_SYMBOLS "0123456789ABCDEF"
#define ERROR_MESSAGE_PREFIX "[ERROR] "
#define ESCAPE_SEQUENCE_BEGIN '{'
#define ESCAPE_SEQUENCE_END '}'
#define INFO_MESSAGE_PREFIX "[INFO] "
#define WARNING_MESSAGE_PREFIX "[WARN] "

#define FORMAT_STRING_ERROR \
    ERROR_MESSAGE_PREFIX "Invalid logging format string.\n"

#define STATIC_ARRAY_LENGTH(array) \
    (sizeof(array) / sizeof((array)[0]))

namespace eon {
namespace core {
    void Log::error(const char* format, ...) {
        this->prepare_error();
        this->print(ERROR_MESSAGE_PREFIX);

        va_list arguments;
        va_start(arguments, format);
        this->print(format, arguments);
        va_end(arguments);

        this->print('\n');
        System::get()->stop(System::HALT);
    }

    void Log::info(const char* format, ...) {
        this->prepare_info();
        this->print(INFO_MESSAGE_PREFIX);

        va_list arguments;
        va_start(arguments, format);
        this->print(format, arguments);
        va_end(arguments);

        this->print('\n');
    }

    void Log::warning(const char* format, ...) {
        this->prepare_warning();
        this->print(WARNING_MESSAGE_PREFIX);

        va_list arguments;
        va_start(arguments, format);
        this->print(format, arguments);
        va_end(arguments);

        this->print('\n');
    }

    void Log::prepare_error() {
    }

    void Log::prepare_info() {
    }

    void Log::prepare_warning() {
    }

    void Log::print(unsigned int integer, size_t base) {
        if (integer == 0) {
            this->print(NUMERIC_BASE_CONVERSION_SYMBOLS[integer]);
            return;
        }
        
        // Reserve 8 chars, which are enough for an 8 bits integer.
        // If it isn't for a full range integer, call recursively until it is.
        char byte[sizeof(char) * (8 + 1)];
        ssize_t i = STATIC_ARRAY_LENGTH(byte) - 1 - 1;
        
        byte[STATIC_ARRAY_LENGTH(byte) - 1] = '\0';
        
        while ((i >= 0) && (integer != 0)) {
            byte[i--] = NUMERIC_BASE_CONVERSION_SYMBOLS[integer % base];
            integer /= base;
        }
        
        if (integer != 0) {
            this->print(integer, base);
        }
        
        this->print(byte + i + 1);
    }

    void Log::print(const char* format, va_list arguments) {
        char* string;
        int integer;
        
        for (; *format != '\0'; ++format) {
            if (*format == ESCAPE_SEQUENCE_END) {
                ++format;
                
                if ((*format != '\0') && (*format == ESCAPE_SEQUENCE_END)) {
                    this->print(ESCAPE_SEQUENCE_END);
                    continue;
                }
                else {
                    this->print("\n" FORMAT_STRING_ERROR);
                    System::get()->stop(System::HALT);
                }
            }
            else if (*format != ESCAPE_SEQUENCE_BEGIN) {
                this->print(*format);
                continue;
            }
            
            ++format;
            
            if (*format == ESCAPE_SEQUENCE_BEGIN) {
                this->print(ESCAPE_SEQUENCE_BEGIN);
                continue;
            }
            
            switch (*format++) {
            case 'c':
                this->print(static_cast<char>(va_arg(arguments, int)));
                break;
            case 's':
                string = va_arg(arguments, char*);
                this->print(string == NULL ? "(null)" : string);
                break;
            case 'i':
                integer = va_arg(arguments, int);
                
                if (*format == 'u') {
                    ++format;
                }
                else if (integer < 0) {
                    this->print('-');
                    integer = -integer;
                }
                
                switch (*format++) {
                case 'b':
                    this->print(integer, 2);
                    this->print('b');
                    break;
                case 'h':
                    this->print(integer, 16);
                    this->print('h');
                    break;
                default:
                    this->print(integer, 10);
                    --format;
                    break;
                }
                
                break;
            default:
                this->print("\n" FORMAT_STRING_ERROR);
                    System::get()->stop(System::HALT);
                break;
            }
            
            if (*format != ESCAPE_SEQUENCE_END) {
                this->print("\n" FORMAT_STRING_ERROR);
                System::get()->stop(System::HALT);
            }
        }
    }
}}