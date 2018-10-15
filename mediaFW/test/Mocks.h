//
// Created by mjonsson on 10/12/18.
//

#include "gtest/gtest.h"

#ifndef MEDIAFW_MOCKS_H
#define MEDIAFW_MOCKS_H

//MOCK_METHOD[n](methodName, returnType(arg1Type, ..., argNType));
//MOCK_CONST_METHOD[n](methodName, returnType(arg1Type, ..., argNType));

#include <Cli.h>

class Mocks_Cli : public Cli {
public:
//    MOCK_METHOD2(generate, double(double, double)); not possible if not virtual method
//
//    MockRng rng;
//    EXPECT_CALL(rng, generate(DoubleEq(0.0), DoubleEq(1.0))
//    .Times(Exactly(1))
//    .WillOnce(Return(0.25));
//    ON_CALL defines stubs
//            EXPECT_CALL defines mocks

//    EXPECT_CALL(mockObject, method(arg1Matcher, ..., argNMatcher))
//    .Times(cardinality)          // 0 or 1
//    .InSequence(sequences)       // 0+
//    .WillOnce(action)            // 0+
//    .WillRepeatedly(action)      // 0 or 1
};


//
//TEST(TestFixture, TestName) {
//    // 1) Create mock objects (collaborators)
//
//    // 2) Specify your expectations of them
//
//    // 3) Construct object(s) under test, passing mocks
//
//    // 4) Run code under test
//
//    // 5) Check output (using Google Test or some other framework)
//
//    // 6) Let gmock automatically check mock expectations were met at
//    //    end of test
//}

#endif //MEDIAFW_MOCKS_H
