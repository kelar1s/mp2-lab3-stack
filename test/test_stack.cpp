#include "../TStack.cpp"
#include "gtest.h"

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> s(10));
}

TEST(TStack, cant_create_stack_with_negatitive_length)
{
	ASSERT_ANY_THROW(TStack<int> s(-10));
}

TEST(TStack, cant_create_too_large_stack)
{
	ASSERT_ANY_THROW(TStack<int> s(MAX_STACK_SIZE + 1));
}

TEST(TStack, can_create_copied_stack)
{
	TStack<int> s(10);
	ASSERT_NO_THROW(TStack<int> s1(s));
}

TEST(TStack, copied_stack_is_equal_to_source_one)
{
	TStack<int> s(10);
	TStack<int> s1(s);
	EXPECT_EQ(s, s1);
}

TEST(TStack, can_set_and_get_element)
{
	TStack<int> s(10);
	ASSERT_NO_THROW(s.Push(5));
	EXPECT_EQ(s.Top(), 5);
	EXPECT_EQ(s.Pop(), 5);
}

TEST(TStack, can_delete_element)
{
	TStack<int> s(2);
	s.Push(1);
	s.Push(2);
	ASSERT_NO_THROW(s.Pop());
	EXPECT_EQ(s.Top(), 1);
}

TEST(TStack, can_clear_stack)
{
	TStack<int> s(5); 
	for (int i = 0; i < s.GetMaxSize(); i++) {
		s.Push(i);
	}
	s.Clear();
	EXPECT_EQ(s.isEmpty(), 1);
}
//SOME EDITS
//SOME EDITS IN TEST-BRANCH
//SOME EDITS IN TEST-BRANCH
TEST(TStack, can_assign_stack_to_itself)
{
	TStack<int> s(4);
	ASSERT_NO_THROW(s = s);
}

TEST(TStack, can_assign_stacks_of_equal_size)
{
	const int size = 4;
	TStack<int> s1(size), s2(size);
	for (int i = 0; i < size; i++) {
		s1.Push(1);
		s2.Push(2);
	}
	ASSERT_NO_THROW(s1 = s2);
}

TEST(TStack, assign_operator_change_stack_size)
{
	const int size1 = 4, size2 = 10;
	TStack<int> s1(size1), s2(size2);
	s1 = s2;
	EXPECT_EQ(10, s1.GetMaxSize());
}

TEST(TStack, can_assign_stacks_of_different_size)
{
	const int size1 = 5, size2 = 10;
	TStack<int> s1(size1), s2(size2);
	for (int i = 0; i < size1; i++)
	{
		s1.Push(i);
	}
	ASSERT_NO_THROW(s2 = s1);
	EXPECT_EQ(s2, s1);
}

TEST(TStack, compare_equal_stacks_return_true)
{
	const int size = 10;
	TStack<int> s1(size), s2(size);
	for (int i = 0; i < size; i++) {
		s1.Push(i);
		s2.Push(i);
	}
	EXPECT_EQ(s1 == s2, 1);
}

TEST(TStack, compare_stack_with_itself_return_true)
{
	const int size = 10;
	TStack<int> s1(size);
	EXPECT_EQ(s1 == s1, 1);
}

TEST(TStack, stacks_with_different_size_are_not_equal)
{
	const int size1 = 5, size2 = 10;
	TStack<int> s1(size1), s2(size2);
	for (int i = 0; i < size1; i++) s1.Push(i);
	for (int j = 0; j < size2; j++) s2.Push(j);
	EXPECT_EQ(s1 != s2, 1);
}

TEST(TStack, when_stack_is_full_cant_set_element)
{
	const int size = 5;
	TStack<int> s(size);
	for (int i = 0; i < size; i++) {
		s.Push(i);
	}
	ASSERT_ANY_THROW(s.Push(10));
}

TEST(TStack, when_stack_is_empty_cant_get_element)
{
	TStack<int> s;
	ASSERT_ANY_THROW(s.Pop());
}


