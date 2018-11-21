#include <string>
#include "../src/expression_search.hpp"
#include "gtest/gtest.h"

namespace {
  TEST(ExpressionSearchTest, LanguageExtensionSupport) {
    const std::string start_dir = "./";
    const std::string language = "ruby";
    const std::vector<std::string> exps;
    const std::string ext = ".rb";
    ExpressionSearch es = ExpressionSearch(start_dir, language, exps);
    EXPECT_TRUE(es.extension_for_lang(language, ext));
  }
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
