#include "AVL.h"
#include "test_utils.h"

template <typename T>
void build_balanced_bst(AVL<T> &tree)
{
  std::vector<T> values = {10, 5, 15, 3, 8, 12, 18, 2, 4, 9, 11};
  for (const T &value : values)
  {
    tree.insert(value);
  }
}

template <typename T>
void insert(AVL<T> &tree, std::vector<T> const& items) {
  for (auto const& it : items) {
    tree.insert(it);
  }
}

template <typename T>
void check_inorder(AVL<T> &tree, std::vector<T> const &inorder)
{
  std::vector<T> result;
  tree.inorder_traversal([&](T value)
                         { result.push_back(value); });
  ASSERT_EQ(result, inorder);
}

template <typename T>
void check_preorder(AVL<T> &tree, std::vector<T> const &preorder)
{
  std::vector<T> result;
  tree.preorder_traversal([&](T value)
                          { result.push_back(value); });
  ASSERT_EQ(result, preorder);
}

TEST(constructor_destructor_const_size_empty, 2)
{
  const AVL<int> tree;
  ASSERT_EQ(tree.size(), 0);
}

TEST(size_after_insert, 2)
{
  AVL<int> tree;
  insert(tree, {1, 2, 3});
  ASSERT_EQ(tree.size(), 3);
}

TEST(insert_balanced_inorder, 2)
{
  AVL<int> tree;
  build_balanced_bst(tree);
  check_inorder(tree, {2, 3, 4, 5, 8, 9, 10, 11, 12, 15, 18});
}

TEST(insert_balanced_preorder, 2)
{
  AVL<int> tree;
  build_balanced_bst(tree);
  check_preorder(tree, {10, 5, 3, 2, 4, 8, 9, 15, 12, 11, 18});
}

TEST(insert_balanced_postorder, 2)
{
  AVL<int> tree;
  build_balanced_bst(tree);
  std::vector<int> postorder = {2, 4, 3, 9, 8, 5, 11, 12, 18, 15, 10};
  std::vector<int> result;
  tree.postorder_traversal([&](int value)
                           { result.push_back(value); });
  ASSERT_EQ(result, postorder);
}

TEST(contains, 5)
{
  AVL<int> tree;
  build_balanced_bst(tree);
  ASSERT(tree.contains(10));
  ASSERT(tree.contains(15));
  ASSERT(tree.contains(18));

  ASSERT(!tree.contains(20));
  ASSERT(!tree.contains(1));
  ASSERT(!tree.contains(13));
  ASSERT(!tree.contains(7));
}

TEST(clear, 5)
{
  AVL<int> tree;
  build_balanced_bst(tree);
  tree.clear();
  ASSERT_EQ(tree.size(), 0);
}

TEST(insert_duplicates, 2)
{
  AVL<int> tree;
  ASSERT_EQ(tree.size(), 0);
  build_balanced_bst(tree);

  ASSERT(tree.size() != 0);
  size_t size = tree.size();

  ASSERT(!tree.insert(2));
  ASSERT(!tree.insert(9));
  ASSERT(!tree.insert(10));
  ASSERT(!tree.insert(15));
  ASSERT(!tree.insert(18));

  ASSERT_EQ(tree.size(), size);
}

TEST(remove_missing, 2)
{
  AVL<int> tree;
  ASSERT_EQ(tree.size(), 0);
  build_balanced_bst(tree);
  ASSERT_EQ(tree.size(), 11);

  ASSERT(tree.size() != 0);
  size_t size = tree.size();

  ASSERT(!tree.remove(20));
  ASSERT(!tree.remove(1));
  ASSERT(!tree.remove(13));
  ASSERT(!tree.remove(7));

  ASSERT_EQ(tree.size(), size);
}

TEST(remove_leaves, 5)
{
  AVL<int> tree;
  build_balanced_bst(tree);

  tree.remove(2);
  tree.remove(4);
  tree.remove(9);
  tree.remove(11);

  check_inorder(tree, {3, 5, 8, 10, 12, 15, 18});
  check_preorder(tree, {10, 5, 3, 8, 15, 12, 18});
}

TEST(remove_single_child, 5)
{
  AVL<int> tree;
  build_balanced_bst(tree);

  tree.remove(8);
  tree.remove(12);

  check_inorder(tree, {2, 3, 4, 5, 9, 10, 11, 15, 18});
  check_preorder(tree, {10, 5, 3, 2, 4, 9, 15, 11, 18});
}

TEST(remove_two_children_simple, 5)
{
  AVL<int> tree;
  build_balanced_bst(tree);

  tree.remove(3);
  tree.remove(15);

  check_inorder(tree, {2, 4, 5, 8, 9, 10, 11, 12, 18});
  check_preorder(tree, {10, 5, 2, 4, 8, 9, 12, 11, 18});
}

TEST(remove_two_children_hard, 5)
{
  AVL<int> tree;
  build_balanced_bst(tree);

  tree.remove(5);
  tree.remove(10);

  check_inorder(tree, {2, 3, 4, 8, 9, 11, 12, 15, 18});
  check_preorder(tree, {9, 4, 3, 2, 8, 15, 12, 11, 18});
}

TEST(abc, 4)
{
  AVL<char> tree;
  insert(tree, {'A', 'B', 'C'});
  check_inorder(tree, {'A', 'B', 'C'});
  check_preorder(tree, {'B', 'A', 'C'});
}

TEST(cba, 4)
{
  AVL<char> tree;
  insert(tree, {'C', 'B', 'A'});
  check_inorder(tree, {'A', 'B', 'C'});
  check_preorder(tree, {'B', 'A', 'C'});
}

TEST(acb, 4)
{
  AVL<char> tree;
  insert(tree, {'A', 'C', 'B'});
  check_inorder(tree, {'A', 'B', 'C'});
  check_preorder(tree, {'B', 'A', 'C'});
}

TEST(cab, 4)
{
  AVL<char> tree;
  insert(tree, {'C', 'A', 'B'});
  check_inorder(tree, {'A', 'B', 'C'});
  check_preorder(tree, {'B', 'A', 'C'});
}

TEST(efcdba, 5)
{
  AVL<char> tree;
  insert(tree, {'E', 'F', 'C', 'D', 'B', 'A'});
  check_inorder(tree, {'A', 'B', 'C', 'D', 'E', 'F'});
  check_preorder(tree, {'C', 'B', 'A', 'E', 'D', 'F'});
}

TEST(efbadc, 5)
{
  AVL<char> tree;
  insert(tree, {'E', 'F', 'B', 'A', 'D', 'C'});
  check_inorder(tree, {'A', 'B', 'C', 'D', 'E', 'F'});
  check_preorder(tree, {'D', 'B', 'A', 'C', 'E', 'F'});
}

TEST(badcef, 5)
{
  AVL<char> tree;
  insert(tree, {'B', 'A', 'D', 'C', 'E', 'F'});
  check_inorder(tree, {'A', 'B', 'C', 'D', 'E', 'F'});
  check_preorder(tree, {'D', 'B', 'A', 'C', 'E', 'F'});
}

TEST(baefcd, 5)
{
  AVL<char> tree;
  insert(tree, {'B', 'A', 'E', 'F', 'C', 'D'});
  check_inorder(tree, {'A', 'B', 'C', 'D', 'E', 'F'});
  check_preorder(tree, {'C', 'B', 'A', 'E', 'D', 'F'});
}

TEST(debac_e, 5)
{
  AVL<char> tree;
  insert(tree, {'D', 'E', 'B', 'A', 'C'});
  tree.remove('E');
  check_inorder(tree, {'A', 'B', 'C', 'D'});
  check_preorder(tree, {'B', 'A', 'D', 'C'});
}

TEST(badce_a, 5)
{
  AVL<char> tree;
  insert(tree, {'B', 'A', 'D', 'C', 'E'});
  tree.remove('A');
  check_inorder(tree, {'B', 'C', 'D', 'E'});
  check_preorder(tree, {'D', 'B', 'C', 'E'});
}

TEST(fcjahkgi_a, 5)
{
  AVL<char> tree;
  insert(tree, {'F', 'C', 'J', 'A', 'H', 'K', 'G', 'I'});
  tree.remove('A');
  check_inorder(tree, {'C', 'F', 'G', 'H', 'I', 'J', 'K'});
  check_preorder(tree, {'H', 'F', 'C', 'G', 'J', 'I', 'K'});
}

TEST(fbjadkce_k, 5)
{
  AVL<char> tree;
  insert(tree, {'F', 'B', 'J', 'A', 'D', 'K', 'C', 'E'});
  tree.remove('K');
  check_inorder(tree, {'A', 'B', 'C', 'D', 'E', 'F', 'J'});
  check_preorder(tree, {'D', 'B', 'A', 'C', 'F', 'E', 'J'});
}

TEST(remove_root_until_empty, 5)
{
  AVL<int> tree;
  build_balanced_bst(tree);

  std::vector<int> to_remove = {10, 9, 8, 5, 4, 3, 2, 15, 12, 11, 18};

  tree.remove(10);
  check_preorder(tree, {9, 5, 3, 2, 4, 8, 15, 12, 11, 18});

  tree.remove(9);
  check_preorder(tree, {8, 3, 2, 5, 4, 15, 12, 11, 18});

  tree.remove(8);
  check_preorder(tree, {5, 3, 2, 4, 15, 12, 11, 18});

  tree.remove(5);
  check_preorder(tree, {4, 3, 2, 15, 12, 11, 18});

  tree.remove(4);
  check_preorder(tree, {12, 3, 2, 11, 15, 18});

  tree.remove(12);
  check_preorder(tree, {11, 3, 2, 15, 18});

  tree.remove(11);
  check_preorder(tree, {3, 2, 15, 18});

  tree.remove(3);
  check_preorder(tree, {15, 2, 18});

  tree.remove(15);
  check_preorder(tree, {2, 18});

  tree.remove(2);
  check_preorder(tree, {18});

  tree.remove(18);
  ASSERT_EQ(tree.size(), 0);
}

TEST(gamut, 5)
{
  AVL<int> tree;
  tree.clear();

  for (int i = 0; i < 100; i++) {
    tree.insert(i);
  }
  tree.clear();
  ASSERT_EQ(tree.size(), 0);

  for (int i = 0; i < 100; i++) {
    tree.insert(i);
  }
  for (int i = 0; i < 100; i++)
  {
    tree.remove(i);
  }
  ASSERT_EQ(tree.size(), 0);

  tree.clear();
  ASSERT_EQ(tree.size(), 0);

  for (int i = 0; i < 100; i++) {
    tree.insert(i);
  }
  for (int i = 0; i < 50; i++)
  {
    tree.remove(i);
  }
  for (int i = 50; i < 100; i++)
  {
    tree.insert(i);
  }

  tree.clear();
}

TEST(performance, 10)
{
  AVL<int> tree;
  Timer timer;
  timer.start();
  int N = 100;
  for (int round = 0; round < 5; round++)
  {
    std::cout << "Round " << round << " (" << N << " items)" << std::endl;
    for (int i = 0; i < N; i++) {
      tree.insert(i);
    }
    ASSERT_EQ(tree.size(), N);
    for (int i = 0; i < tree.size(); i++)
    {
      tree.remove(i);
    }
    tree.clear();
    N *= 10;
    if (timer.seconds() > 20)
    {
      PARTIAL_CREDIT(round / 5.0);
    }
  }
}

DO_VALGRIND(5);

TEST_MAIN();