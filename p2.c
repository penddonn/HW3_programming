/* CS100 Fall 2026 - HW3 Problem 2: Palindrome
 *
 * Read n strings and test whether each of them is a palindrome.
 * Print "Yes" / "No" on one line per string.
 * Use dynamic memory to store each input string (no fixed-size arrays).
 * Do not rename this file.
 */
#include <stdio.h>
#include <stdlib.h>

static int is_space(int c)
{
    return c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\v' || c == '\f';
}

/* Read one whitespace-free token into a heap buffer.
 * `hint` is the announced length, used as the initial capacity; the buffer
 * grows if the token turns out to be longer. Returns NULL on failure. */
static char *read_token(size_t hint, size_t *out_len)
{
    size_t cap = hint + 1;
    size_t len = 0;
    char *buf = malloc(cap);
    int c;

    if (buf == NULL)
        return NULL;

    do {
        c = getchar();
    } while (c != EOF && is_space(c));

    while (c != EOF && !is_space(c)) {
        if (len + 1 >= cap) {
            char *tmp;
            cap *= 2;
            tmp = realloc(buf, cap);
            if (tmp == NULL) {
                free(buf);
                return NULL;
            }
            buf = tmp;
        }
        buf[len++] = (char)c;
        c = getchar();
    }
    buf[len] = '\0';
    *out_len = len;
    return buf;
}

static int is_palindrome(const char *s, size_t len)
{
    size_t i = 0, j;
    if (len == 0)
        return 1;
    j = len - 1;
    while (i < j) {
        if (s[i] != s[j])
            return 0;
        ++i;
        --j;
    }
    return 1;
}

int main(void)
{
    long long n;
    long long k;

    if (scanf("%lld", &n) != 1)
        return 0;

    for (k = 0; k < n; ++k) {
        size_t hint, len;
        char *str;

        if (scanf("%zu", &hint) != 1)
            break;
        str = read_token(hint, &len);
        if (str == NULL)
            return 1;
        puts(is_palindrome(str, len) ? "Yes" : "No");
        free(str);
    }
    return 0;
}
