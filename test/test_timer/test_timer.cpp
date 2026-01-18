#include <unity.h>
#include "../../src/Utils/Timer.h"

// External mock millis control
extern unsigned long _mockMillis;

void setUp(void) {
    // Start from 1 since Timer treats _timer=0 as stopped
    _mockMillis = 1;
}

void tearDown(void) {
}

void test_timer_default_constructor() {
    Timer timer;
    
    // Should not be ready immediately (not started)
    TEST_ASSERT_FALSE(timer.ready());
}

void test_timer_constructor_with_period() {
    _mockMillis = 1;
    Timer timer(1000);
    
    // Should not be ready immediately after creation
    TEST_ASSERT_FALSE(timer.ready());
}

void test_timer_ready_after_period() {
    _mockMillis = 1;
    Timer timer(1000);
    
    _mockMillis = 1000;
    TEST_ASSERT_FALSE(timer.ready());
    
    _mockMillis = 1001;
    TEST_ASSERT_TRUE(timer.ready());
}

void test_timer_auto_restart() {
    _mockMillis = 1;
    Timer timer(1000);
    
    _mockMillis = 1001;
    TEST_ASSERT_TRUE(timer.ready());
    
    // After ready(), timer should auto-restart from current millis
    _mockMillis = 1500;
    TEST_ASSERT_FALSE(timer.ready());
    
    _mockMillis = 2001;
    TEST_ASSERT_TRUE(timer.ready());
}

void test_timer_start_with_new_period() {
    _mockMillis = 1;
    Timer timer;
    
    timer.start(500);
    
    _mockMillis = 500;
    TEST_ASSERT_FALSE(timer.ready());
    
    _mockMillis = 501;
    TEST_ASSERT_TRUE(timer.ready());
}

void test_timer_start_without_period() {
    _mockMillis = 1;
    Timer timer(1000);
    
    _mockMillis = 1001;
    TEST_ASSERT_TRUE(timer.ready());
    
    _mockMillis = 1500;
    timer.start();  // Restart with same period from current time
    
    _mockMillis = 2000;
    TEST_ASSERT_FALSE(timer.ready());
    
    _mockMillis = 2500;
    TEST_ASSERT_TRUE(timer.ready());
}

void test_timer_stop() {
    _mockMillis = 1;
    Timer timer(1000);
    
    timer.stop();
    
    _mockMillis = 2000;
    TEST_ASSERT_FALSE(timer.ready());
}

void test_timer_multiple_cycles() {
    _mockMillis = 1;
    Timer timer(100);
    
    for (int cycle = 1; cycle <= 5; ++cycle) {
        _mockMillis += 100;
        TEST_ASSERT_TRUE_MESSAGE(timer.ready(), "Timer should fire each cycle");
    }
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    RUN_TEST(test_timer_default_constructor);
    RUN_TEST(test_timer_constructor_with_period);
    RUN_TEST(test_timer_ready_after_period);
    RUN_TEST(test_timer_auto_restart);
    RUN_TEST(test_timer_start_with_new_period);
    RUN_TEST(test_timer_start_without_period);
    RUN_TEST(test_timer_stop);
    RUN_TEST(test_timer_multiple_cycles);
    
    return UNITY_END();
}
