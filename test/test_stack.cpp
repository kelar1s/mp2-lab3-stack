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

TEST(TVector, can_set_and_get_element)
{
	TStack<int> s(4);
	ASSERT_NO_THROW(s.Push(5));
	EXPECT_EQ(s.Top(), 5);
}

TEST(TVector, can_delete_element)
{
	TStack<int> s(2);
	s.Push(1);
	s.Push(2);
	ASSERT_NO_THROW(s.Pop());
	EXPECT_EQ(s.Top(), 1);
}

TEST(TVector, can_clear_stack)
{
	TStack<int> s(5);
	for (int i = 0; i < s.GetMaxSize(); i++) {
		s.Push(i);
	}
	s.Clear();
	EXPECT_EQ(s.isEmpty(), 1);
}