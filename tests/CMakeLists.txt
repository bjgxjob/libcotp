
IF(BUILD_TESTING)
    add_executable (test_cotp ../src/otp.c check_otp.c)

    target_link_libraries (test_cotp -lcriterion -lbaseencode -lgcrypt)

    add_test (NAME TestCOTP COMMAND test_cotp)
ENDIF(BUILD_TESTING)
