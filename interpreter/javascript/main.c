#include <stdlib.h>
#include <unistd.h>
#include "Input.h"
#include "Token.h"

int main() {
    bool has_err = false;

    struct k_Input* stdin_input = k_Input_from_fd(
        STDIN_FILENO, "<stdin>", &has_err);

    if (has_err) {
        return EXIT_FAILURE;
    }

    while (true) {
        struct k_Token* token = k_Token_parse(stdin_input, &has_err);

        if (token == NULL) {
            break;
        }

        printf("%d[%.*s]", token->type, (int) token->str->len, token->str->val);
        K_REF_DEC(token);
    }

    K_REF_DEC(stdin_input);
    return has_err ? EXIT_FAILURE : EXIT_SUCCESS;
}
