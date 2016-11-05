//
// Created by user on 7/26/16.
//

#include <gmock/gmock.h>

#include "index/Indexer.h"
#include "indexatorHeader.h"

TEST (indexator, shouldSplitIntoTokens) {
    Indexer i;

    EXPECT_THAT (i.tokenize (pageText), ::testing::ContainerEq (expectedTokens));
}
