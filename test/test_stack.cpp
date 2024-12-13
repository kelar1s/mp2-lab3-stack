#include "../TStack.cpp"
#include "gtest.h"

TEST(TStack, can_create_stack)
{
  ASSERT_NO_THROW(TStack<int> s);
}

TEST(TStack, can_create_copied_stack)
{
	TStack<int> s;
	ASSERT_NO_THROW(TStack<int> s1(s));
}

TEST(TStack, copied_stack_is_equal_to_source_one)
{
	TStack<int> s;
	TStack<int> s1(s);
	EXPECT_EQ(s, s1);
}

TEST(TStack, can_set_and_get_element)
{
	TStack<int> s;
	ASSERT_NO_THROW(s.Push(5));
	EXPECT_EQ(s.Top(), 5);
	EXPECT_EQ(s.Pop(), 5);
}

TEST(TStack, can_delete_element)
{
	TStack<int> s;
	s.Push(1);
	s.Push(2);
	ASSERT_NO_THROW(s.Pop());
	EXPECT_EQ(s.Top(), 1);
}

TEST(TStack, can_clear_stack)
{
	TStack<int> s; 
	for (int i = 0; i < 10; i++) {
		s.Push(i);
	}
	ASSERT_NO_THROW(s.Clear());
	EXPECT_EQ(s.isEmpty(), true);
}

TEST(TStack, can_assign_stack_to_itself)
{
	TStack<int> s;
	ASSERT_NO_THROW(s = s);
}

TEST(TStack, can_assign_stacks_of_equal_size)
{
	const int a = 10;
	TStack<int> s1, s2;
	for (int i = 0; i < a; i++) {
		s1.Push(1);
		s2.Push(2);
	}
	ASSERT_NO_THROW(s1 = s2);
}

TEST(TStack, can_assign_stacks_of_different_size)
{
	const int a = 5, b = 10;
	TStack<int> s1, s2;
	for (int i = 0; i < a; i++)
	{
		s1.Push(i);
	}
	ASSERT_NO_THROW(s2 = s1);
	EXPECT_EQ(s2, s1);
}

TEST(TStack, compare_equal_stacks_return_true)
{
	TStack<int> s1, s2;
	for (int i = 0; i < 10; i++) {
		s1.Push(i);
		s2.Push(i);
	}
	EXPECT_EQ(s1 == s2, true);
}

TEST(TStack, compare_stack_with_itself_return_true)
{
	TStack<int> s;
	s.Push(5);
	s.Push(10);
	EXPECT_EQ(s == s, true);
}

TEST(TStack, different_stacks_are_not_equal)
{
	TStack<int> s1, s2;
	for (int i = 0; i < 10; i++) s1.Push(i);
	for (int j = 0; j < 5; j++) s2.Push(j);
	EXPECT_EQ(s1 != s2, true);
}

TEST(TStack, when_stack_is_empty_cant_get_element)
{
	TStack<int> s;
	ASSERT_ANY_THROW(s.Pop());
}
