using System.Collections;

namespace ws2
{
    public partial class List 
    {
        public class ListNode : IEnumerator
        {
            internal int idx;
            internal List cpy;

            public ListNode(List l)
            {
                idx = 0;
                cpy = l;
            }

            public object Current
            {
                get
                {
                    return cpy[idx].data;
                }
            }

            public bool MoveNext()
            {
                ++idx;

                return (null != cpy[idx]);
            }

            public void Reset()
            {
                throw new System.NotImplementedException();
            }
        };
    }
}
