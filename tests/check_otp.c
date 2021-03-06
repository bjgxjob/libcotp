#include <criterion/criterion.h>
#include <string.h>
#include <cotp.h>
#include <baseencode.h>


Test(totp_rfc6238, test_8_digits_sha1) {
    const char *K = "12345678901234567890";
    const int digits = 8;
    const int64_t counter[] = {59, 1111111109, 1111111111, 1234567890, 2000000000, 20000000000};
    const char *expected_totp[] = {"94287082", "07081804", "14050471", "89005924", "69279037", "65353130"};

    char *K_base32 = base32_encode(K, strlen(K)+1);

    for (int i = 0; i < 6; i++) {
        char *totp = get_totp_at(K_base32, counter[i], digits, SHA1);
        cr_expect_str_eq(totp, expected_totp[i], "Expected %s to be equal to %s\n", totp, expected_totp[i]);
        free(totp);
    }

    free(K_base32);
}


Test(totp_rfc6238, test_8_digits_sha256) {
    const char *K = "12345678901234567890123456789012";
    const int digits = 8;
    const int64_t counter[] = {59, 1111111109, 1111111111, 1234567890, 2000000000, 20000000000};
    const char *expected_totp[] = {"46119246", "68084774", "67062674", "91819424", "90698825", "77737706"};

    char *K_base32 = base32_encode(K, strlen(K)+1);

    for (int i = 0; i < 6; i++) {
        char *totp = get_totp_at(K_base32, counter[i], digits, SHA256);
        cr_expect_str_eq(totp, expected_totp[i], "Expected %s to be equal to %s\n", totp, expected_totp[i]);
        free(totp);
    }

    free(K_base32);
}


Test(totp_rfc6238, test_8_digits_sha512) {
    const char *K = "1234567890123456789012345678901234567890123456789012345678901234";
    const int digits = 8;
    const int64_t counter[] = {59, 1111111109, 1111111111, 1234567890, 2000000000, 20000000000};
    const char *expected_totp[] = {"90693936", "25091201", "99943326", "93441116", "38618901", "47863826"};

    char *K_base32 = base32_encode(K, strlen(K)+1);

    for (int i = 0; i < 6; i++) {
        char *totp = get_totp_at(K_base32, counter[i], digits, SHA512);
        cr_expect_str_eq(totp, expected_totp[i], "Expected %s to be equal to %s\n", totp, expected_totp[i]);
        free(totp);
    }

    free(K_base32);
}


Test(hotp_rfc, test_6_digits) {
    const char *K = "12345678901234567890";
    const int digits = 6;
    const int counter[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const char *expected_hotp[] = {"755224", "287082", "359152", "969429", "338314", "254676", "287922", "162583", "399871", "520489"};

    char *K_base32 = base32_encode(K, strlen(K)+1);

    for (int i = 0; i < 10; i++) {
        char *hotp = get_hotp(K_base32, counter[i], digits, SHA1);
        cr_expect_str_eq(hotp, expected_hotp[i], "Expected %s to be equal to %s\n", hotp, expected_hotp[i]);
        free(hotp);
    }

    free(K_base32);
}
