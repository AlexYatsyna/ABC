#include "ll_cycle.h"

bool ll_has_cycle(node *head) {
    /* Ваш код должен быть написан только внутри этой функции */
    node *head2 = head;
    bool isFirst=true;
    if (head == nullptr)
    {
        return false;
    }
    while (true)
    {
        if(head == head2 && !isFirst )
        {
            break;
        }
        else
        {
            if(head->next != nullptr)
            {
            head = head->next;
            }
            for(int i=0;i<2;i++)
            {
                if (head2->next == nullptr)
                {
                    return false;
                }
                else 
                {
                    head2=head2->next;
                }
            }
        }
        isFirst=false;
        
    }
    return true;
}
