#include "Tree.h"


void Tree::Print()
{
    COORD currentCursorPosition = Cursor::GetConsoleCursorPosition();
    PrintTree(head, 20, currentCursorPosition.Y, 2, 'H');
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void Tree::PrintTree(Node* root, short x, short y, short a, char childPos)
{
    if (root)
    {
        if (a > 0 && childPos != 'H') //
        {
            if (childPos == 'L')
                x -= 10;
            else
                x += 10;
        }
        else
        {
            if (childPos != 'k')
            {
                if (childPos == 'L')
                    x -= 4;
                else
                    x += 4;
            }
            
        }
            

        Cursor::GoToXY(x, y += 2);
        a--;

        printf("%5d", root->key);
        PrintTree(root->childLeft, x, y, a, 'L');
        PrintTree(root->childRight, x, y, a, 'R');
    }
}
