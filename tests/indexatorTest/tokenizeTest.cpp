//
// Created by user on 7/26/16.
//

#include <gmock/gmock.h>

#include "index/Worker.h"
#include "indexatorHeader.h"

TEST (indexator, shouldSplitIntoTokens) {
    Worker i;

    EXPECT_THAT (i.tokenize (pageText), ::testing::ContainerEq (expectedTokens));
}
