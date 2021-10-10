namespace ws2
{

    internal class Node
    {
        internal object data;
        internal Node _next;
        public Node(object _data = null)
        {
            data = _data;
            _next = null;
        }
        public Node Next()
        {
            return _next;
        }
    };


    public partial class List 
    {

        internal Node head;

        internal int size;
        public List()
        {
            head = new Node(null);
            head._next = null;

            size = 0;
        }
        public bool IsEmpty()
        {
            return Count() == 0;
        }

        public void Clear()
        {
            size = 0;
            head._next = null;
            return;
        }

        public int Count()
        {
            return size;
        }

        public void Push(object _data)
        {
            Node cur = head;
            Node new_node = new Node(_data);
            while (cur._next != null)
            {
                cur = cur.Next();
            }
            cur._next = new_node;
            ++size;
            return;
        }

        public object Pop()
        {
            Node head_next_next = null;
            object head_next = head._next;
            if (head_next != null)
            {
                head_next_next = head._next._next;
                head._next = head_next_next;
                head_next = ((Node)head_next).data;
                --size;
            }
            return head_next;
        }


        public object Peek()
        {
            if (Count() > 0)
            {
                return head._next.data;
            }
            return null;
        }

        internal Node this[int i]
        {
            get
            {
                return FindNode(i);
            }
        }

        internal Node FindNode(int i)
        {
            int j = 0;
            Node cur = head;
            Node new_node = null;

            while (j < this.Count() && cur._next != null)
            {
                cur = cur.Next();
                if (j == i)
                {
                    new_node = new Node(cur.data);
                    break;
                }
                ++j;
            }

            return new_node;
        }

        public ListNode GetEnumerator()
        {
            return new ListNode(this);
        }
    }
}
