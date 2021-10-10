using System;
using System.Collections.Generic;
using System.Text;

namespace ws2
{
    class HelperStack
    {
        public HelperStack() {;}
        public const int DEFULT_SIZE = 10;
        public const int START_IDX = -1;
    }
    class Stack
    {
        public Stack()
        {
            stackArray = new object[HelperStack.DEFULT_SIZE];
            capacity = HelperStack.DEFULT_SIZE;
            top = HelperStack.START_IDX;
        }
        public Stack(int size)
        {
            stackArray = new object[size];
            capacity = size;
            top = HelperStack.START_IDX;
        }

        public void StackPush(object obj)
        {
            if (top >= capacity)
            {
                return;
            }
            ++top;
            stackArray[top] = obj;
            return;
        }
        public object StackPeek()
        {
            if (top > HelperStack.START_IDX)
            {
                return (stackArray[top]);
            }
            return null;
        }
        public object StackPop()
        {
            object tmp = null;
            if (top > HelperStack.START_IDX)
            {
                tmp = stackArray[top];
                --top;
            }

            return tmp;
        }
        public void StackClear()
        {
            Array.Clear(stackArray, HelperStack.START_IDX + 1, top);
            top = HelperStack.START_IDX;
            return ;
        }
        public bool StackIsEmpty()
        {
            return (top == HelperStack.START_IDX);
        }
        public int StackSize()
        {
            return (top);
        }
        public int StackCapacity()
        {
            return (capacity);
        }

        private object[] stackArray;
        private int top;
        readonly int capacity;
    }
}
