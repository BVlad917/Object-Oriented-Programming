//
// Created by VladB on 19-Sep-21.
//

#include <stdio.h>
#include <assert.h>
#define MAXLENGTH 100

// ============================================================================================
// ===== The Business Layer; Handles all the functionalities, calculations of the program =====
// ============================================================================================

int is_prime(int n) {
    /*
    Checks if a given integer n is prime or not.
    :param: n - integer
    :returns: 1 if n is prime, 0 otherwise
    */
    // If n <= 1 then it is not prime
    if (n <= 1) {
        return 0;
    }
    // If n is 2 then it is prime
    if (n == 2) {
        return 1;
    }
    // If n is even then it is prime
    if (n % 2 == 0) {
        return 0;
    }
    // If neither of the above is true, we search for a divisor of n up to sqrt(n). If we find one then
    // n is not prime. If we get to the end of the loop, then n is prime
    for (int d = 3; d * d <= n; d += 2) {
        if (n % d == 0) {
            return 0;
        }
    }
    return 1;
}


int find_smaller_primes(int n, int smaller_primes[]) {
    /*
    Finds all the prime numbers smaller than a given integer n and stores them in the given vector <smaller_primes>.
    Returns the length of the vector <smaller_primes>.
    */
    // There are no primes smaller than 2
    if (n <= 2) {
        return 0;
    }
    else {
        // We iterate over all odd numbers in the interval [3, n) and each time we find a prime we add it to
        // the vector. At the end we return the lenght of this vector.
        int cnt = 1;
        smaller_primes[0] = 2;
        for (int d = 3; d < n; d += 2) {
            if (is_prime(d)) {
                smaller_primes[cnt] = d;
                cnt = cnt + 1;
            }
        }
        return cnt;
    }
}

int find_longest_subseq(int n, int a[], int longest_subseq[]) {
    /*
    Finds the longest increasing contiguous subsequence in the array <a> such that the sum of any 2
    consecutive elements is a prime number and stores this subsequence in the vector <longest_subseq>.
    Returns the length of the vector <longest_subseq>.
    */
    int i, max_len, left, right, len_dp, dp[MAXLENGTH];
    max_len = 1;
    right = 0;
    // At each position the array <dp> stores the length of the longest subsequence with the above conditions
    // that ends with the element from that position in the vector <a>.
    dp[0] = 1;
    for (i = 1; i < n; i++) {
        if (a[i] > a[i - 1] && is_prime(a[i] + a[i - 1])) {
            dp[i] = dp[i - 1] + 1;
            if (dp[i] > max_len) {
                // We save the maximum length of the array <dp> and mark the index i where this maximum appears
                // as the right bound of the subsequence
                max_len = dp[i];
                right = i;
            }
        }
        else {
            dp[i] = 1;
        }
    }
    // Using the right bound of the subsequence we find the left bound
    left = right;
    while (dp[left] != 1) {
        left = left - 1;
    }
    // Now that we know where the subsequence we need is, we can just iterate these elements and
    // save them in an array
    len_dp = 0;
    for (i = left; i <= right; i++) {
        longest_subseq[len_dp] = a[i];
        len_dp = len_dp + 1;
    }
    return len_dp;
}

int greatest_common_div(int a, int b) {
    /*
    Finds the greatest common divisor between two given integers <a> and <b> and returns it.
    */
    while (a != b) {
        if (a > b) {
            a = a - b;
        }
        else {
            b = b - a;
        }
    }
    return a;
}

int find_primes_to_n(int n, int primes[]) {
    /*
    Finds all the numbers smaller than n and greater than 0 which are realtively prime to n.
    Returns the length of the array made of these numbers.
    */
    int i, len = 0;
    for (i = 1; i < n; i++) {
        if (greatest_common_div(n, i) == 1) {
            primes[len] = i;
            len = len + 1;
        }
    }
    return len;
}

// ==========================================================
// ===== The User Interface (UI) layer; Handles the I/O =====
// ==========================================================

void ui_solve_pb1() {
    /*
    Handles the I/O related to the first functionality of the program. Prints messages in the console asking for
    user input and then it reads this user input.
    */
    int n, smaller_primes[MAXLENGTH], count_smaller_primes;
    printf("Please give the number n: ");
    scanf("%d", &n);
    count_smaller_primes = find_smaller_primes(n, smaller_primes);
    if (n == 0) {
        printf("There are primes smaller than %d.\n", n);
    }
    else {
        printf("We've found %d prime numbers smaller than %d are: ", count_smaller_primes, n);
        for (int i = 0; i < count_smaller_primes; i++) {
            printf("%d ", smaller_primes[i]);
        }
        printf("\n");
    }
}

void ui_solve_pb2() {
    /*
    Handles the I/O related to the second functionality of the program. Prints messages in the console asking for
    user input and then it reads this user input.
    */
    int n, i, len_longest_subseq, a[MAXLENGTH], longest_subseq[MAXLENGTH];
    printf("How many numbers do you want the vector to have: ");
    scanf("%d", &n);
    printf("Please give the numbers: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    len_longest_subseq = find_longest_subseq(n, a, longest_subseq);
    if (len_longest_subseq == 0) {
        printf("There is no such subsequence.\n");
    }
    else {
        printf("The subsequence is: ");
        for (i = 0; i < len_longest_subseq; i++) {
            printf("%d ", longest_subseq[i]);
        }
        printf("\n");
    }
}

void ui_solve_pb3() {
    /*
    Handles the I/O related to the third functionality of the program. Prints messages in the console asking for
    user input and then it reads this user input.
    */
    int n, i, len_primes, primes[MAXLENGTH];
    printf("Give the number n: ");
    scanf("%d", &n);
    len_primes = find_primes_to_n(n, primes);
    if (len_primes == 0) {
        printf("There are no numbers smaller than n that are prime relative to n.\n");
    }
    else {
        printf("The numbers are: ");
        for (i = 0; i < len_primes; i++) {
            printf("%d ", primes[i]);
        }
        printf("\n");
    }

}

void print_menu() {
    /*
    Prints the menu with the currently available commands.
    */
    printf("These are the currently available commands:\n"
           "1 - Generate all the prime numbers smaller than a given natural number n\n"
           "2 - Find the longest increasing contiguous subseq., such the sum of that any 2 cons."
           "elements is a prime number\n"
           "3 - Determine all the numbers smaller than n that are relatively prime to n\n"
           "0 - Exit\n");
}

int read_command() {
    /*
    Reads the command that the user wants to execute. In case an invalid command is given, an error message is shown
    in the console.
    Returns the command number given by the user (1, 2, 3, or 0).
    */
    int cmd;
    print_menu();
    while (1) {
        printf("\nPlease enter a valid command: ");
        scanf("%d", &cmd);
        if (cmd == 1 || cmd == 2 || cmd == 3 || cmd == 0) {
            break;
        }
        else {
            printf("Invalid command.");
        }
        printf("\n");
    }
    return cmd;
}

void ui_start_program() {
    /*
    Function which starts the execution of the program. It reads a command from the console and then calls the
    function that solves the functionality related to that command (or exits the program).
    */
    int cmd;
    printf("Hello you!\n");
    while (1) {
        cmd = read_command();
        if (cmd == 1) {
            ui_solve_pb1();
        }
        else if (cmd == 2) {
            ui_solve_pb2();
        }
        else if (cmd == 3) {
            ui_solve_pb3();
        }
        else{
            printf("The program will exit. Bye!\n");
            break;
        }
    }

}

// =================
// ===== Tests =====
// =================

void test_is_prime() {
    assert(is_prime(1) == 0);
    assert(is_prime(2) == 1);
    assert(is_prime(3) == 1);
    assert(is_prime(4) == 0);
    assert(is_prime(10) == 0);
    assert(is_prime(11) == 1);
}

void test_smaller_primes() {
    int n = 5, len_smaller_primes, smaller_primes[MAXLENGTH];
    len_smaller_primes = find_smaller_primes(n, smaller_primes);
    assert(len_smaller_primes == 2);
    assert(smaller_primes[0] == 2);
    assert(smaller_primes[1] == 3);
    n = 10;
    len_smaller_primes = find_smaller_primes(n, smaller_primes);
    assert(len_smaller_primes == 4);
    assert(smaller_primes[0] == 2);
    assert(smaller_primes[1] == 3);
    assert(smaller_primes[2] == 5);
    assert(smaller_primes[3] == 7);
    n = 24;
    len_smaller_primes = find_smaller_primes(n, smaller_primes);
    assert(len_smaller_primes == 9);
    len_smaller_primes = find_smaller_primes(1, smaller_primes);
    assert(len_smaller_primes == 0);
    len_smaller_primes = find_smaller_primes(2, smaller_primes);
    assert(len_smaller_primes == 0);
    len_smaller_primes = find_smaller_primes(3, smaller_primes);
    assert(len_smaller_primes == 1);
}

void test_find_longest_subseq() {
    int len_longest_subseq, a[MAXLENGTH], longest_subseq[MAXLENGTH];
    a[0] = 5;
    a[1] = 6;
    a[2] = 4;
    a[3] = 7;
    a[4] = 10;
    a[5] = 1;
    a[6] = 2;
    len_longest_subseq = find_longest_subseq(7, a, longest_subseq);
    assert(len_longest_subseq == 3);
    assert(longest_subseq[0] == 4);
    assert(longest_subseq[1] == 7);
    assert(longest_subseq[2] == 10);

    // 2 subsequences of the same length ==> the function picks the first one
    a[0] = 5;
    a[1] = 6;
    a[2] = 7;
    a[3] = 4;
    a[4] = 7;
    a[5] = 10;
    a[6] = 1;
    a[7] = 2;
    len_longest_subseq = find_longest_subseq(8, a, longest_subseq);
    assert(len_longest_subseq == 3);
    assert(longest_subseq[0] == 5);
    assert(longest_subseq[1] == 6);
    assert(longest_subseq[2] == 7);
    // No increasing contiguous subsequence where any 2 consecutive elements have as their sum a prime number
    // So the function just picks the first number from the vector and places it in the list
    a[0] = 10;
    a[1] = 9;
    a[2] = 8;
    a[3] = 7;
    len_longest_subseq = find_longest_subseq(4, a, longest_subseq);
    assert(len_longest_subseq == 1);
    assert(longest_subseq[0] == 10);
}

void test_greatest_common_div() {
    assert(greatest_common_div(10, 5) == 5);
    assert(greatest_common_div(12, 7) == 1);
    assert(greatest_common_div(9, 3) == 3);
    assert(greatest_common_div(17, 17) == 17);
}

void test_find_primes_to_n() {
    int len_primes, primes[MAXLENGTH];
    len_primes = find_primes_to_n(10, primes);
    assert(len_primes == 4);
    assert(primes[0] == 1);
    assert(primes[1] == 3);
    assert(primes[2] == 7);
    assert(primes[3] == 9);

    len_primes = find_primes_to_n(7, primes);
    assert(len_primes == 6);
    assert(primes[0] == 1);
    assert(primes[1] == 2);
    assert(primes[2] == 3);
    assert(primes[3] == 4);
    assert(primes[4] == 5);
    assert(primes[5] == 6);
}

void run_all_tests() {
    test_is_prime();
    test_smaller_primes();
    test_find_longest_subseq();
    test_greatest_common_div();
    test_find_primes_to_n();
}

// =================================
// ===== The main function  ===== //
// =================================

int main() {
    run_all_tests();
    ui_start_program();
    return 0;
}
