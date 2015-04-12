
#include <string>
#include "gtest/gtest.h"

namespace alg {

#define MAX_ALPHABET (26)
#define CHR_TO_IDX(ch) ((ch|32) - 'a')

class Trie {
public:

  Trie() {
    memset(children, 0, sizeof(children));
  }

  std::string value;
  Trie* children[MAX_ALPHABET];
};


Trie* GetNode() {
  return new Trie();
}

Trie* root = GetNode();

void Insert(Trie* trie, const std::string& key) {
  int index = 0;
  for (size_t i = 0; i < key.length(); ++i) {
    index = CHR_TO_IDX(key[i]);
    if (trie->children[index] == nullptr) {
      trie->children[index] = GetNode();
    }
    trie = trie->children[index];
  }
  trie->value = key;
}

bool Seach(Trie* trie, const std::string& key) {
  int index = 0;
  for (size_t i = 0; i < key.length(); ++i) {
    index = CHR_TO_IDX(key[i]);
    if (trie->children[index] == nullptr) {
      return false;
    }
    trie = trie->children[index];
  }
  return true;
}

}  // namespace alg


TEST(Trie, Trie) {
  alg::Insert(alg::root, "hello");
  alg::Insert(alg::root, "lazy");
  alg::Insert(alg::root, "fox");
  alg::Insert(alg::root, "jump");
  alg::Insert(alg::root, "over");
  alg::Insert(alg::root, "zhe");
  alg::Insert(alg::root, "dog");


  EXPECT_TRUE(alg::Seach(alg::root, "hello"));
  EXPECT_TRUE(alg::Seach(alg::root, "hell"));
  EXPECT_TRUE(alg::Seach(alg::root, "jump"));
  EXPECT_TRUE(alg::Seach(alg::root, "dog"));
  EXPECT_FALSE(alg::Seach(alg::root, "dogg"));
  EXPECT_FALSE(alg::Seach(alg::root, "ovr"));
}