#include <iostream>
#include <stack>
#include <bitset>

using byte = std::uint8_t;

struct Node
{
    Node(byte pos)
    : mask(128 >> pos)
    , downMask(0)
    , leftMask(0)
    , rightMask(0)
    {}

    Node(const Node& prev, byte pos)
    : mask(128 >> pos)
    , downMask(prev.downMask | prev.mask)
    , leftMask((prev.leftMask | prev.mask ) << 1)
    , rightMask((prev.rightMask | prev.mask) >> 1)
    {}

    byte mask;

    byte nextChild = 0;

    // Cache : previous masks
    byte downMask;
    byte leftMask;
    byte rightMask;

    bool isLegal() const
    {
        return (mask & (downMask | leftMask | rightMask)) == 0;
    }
};

void printStack(std::stack<Node>& stack)
{
    std::cout << " == SOLUTION == " << std::endl;
    while(!stack.empty())
    {
        std::cout << std::bitset<8>(stack.top().mask) << std::endl;
        stack.pop();
    }
}

void solve()
{
    for (byte i = 0; i < 8; ++i)
    {
        std::stack<Node> stack;
        stack.push(Node(i));

        while (!stack.empty())
        {
            auto& top = stack.top();

            // Complete ?
            if (stack.size() == 8)
            {
                printStack(stack);
                break;
            }

            if (top.nextChild != 8)
            {
                Node next(top, top.nextChild++);
                if (next.isLegal())
                {
                    stack.push(next);
                }
                continue;
            }

            stack.pop();
        }
    }
}

int main()
{
    solve();
}
