#include <cassert>
#include <cmath>
#include <string>

// https://leetcode.com/problems/palindrome-number/
// https://godbolt.org/z/94W37e


auto count_digits(int num) {
    auto count = 1UL;
    while(num /= 10) {
        ++count;
    }
    return count;
}

class Solution {
public:
    static bool isPalindrome(const int x) {
        if (x < 0) return false;
        if (x < 10) return true;
        const std::string str = std::to_string(x);
        auto rev = str.cend();
        auto fwd = str.cbegin();
        while(fwd < rev) {
            rev = std::prev(rev);
            if (*fwd != *rev) return false;
            std::advance(fwd, 1);
        }
        return true;
    }

    static bool isPalindromeNonString(const int x) {
        if (x < 0) return false;
        if (x < 10) return true;
        auto right_func( [x = x] () mutable { const auto ret = x % 10; x /= 10 ; return ret; } );
        const auto digits = count_digits(x);
        auto left_func( [x = x, digits = digits] () mutable -> int {
            auto left_shift = std::pow(10, digits - 1);
            --digits;
            const int ret = static_cast<int>(x / left_shift);
            x = x - (ret * left_shift);
            return ret;
        } );
        auto d_count = digits;
        while (d_count--) {
            const auto r = right_func();
            const auto l = left_func();
            if (r != l) return false;
        }
        return true;
    }
};

int main() {
    assert(Solution::isPalindrome(-124) == false);
    assert(Solution::isPalindrome(121) == true);
    assert(Solution::isPalindrome(122) == false);
    assert(Solution::isPalindrome(1223) == false);
    assert(Solution::isPalindrome(1221) == true);

    assert(Solution::isPalindromeNonString(-124) == false);
    assert(Solution::isPalindromeNonString(121) == true);
    assert(Solution::isPalindromeNonString(122) == false);
    assert(Solution::isPalindromeNonString(1223) == false);
    assert(Solution::isPalindromeNonString(1221) == true);
    return 0;
}
