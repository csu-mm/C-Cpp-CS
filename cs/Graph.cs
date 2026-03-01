    public class TestGraph
    {
        // Visit vertex
        // explore vertex
        // BFS / spanning tree
        //      create a Queue
        //  initial step: start exploration from any vertex
        //      add inital/start node in queue
        //      add this node in the result
        //  repeating steps:
        //      take out the vertex from queue and start exporing that vertex
        //      if this vertex not in result, add connected vertex in queue and add the same to the result  
        //      when all edges visited, repeat the repeated steps
        //
        // DFS // Deepth First Search  // DFS spanning tree
        // DFS result: 
        //  create a stack
        // initial steps : start exploration from any vertex
        //      add inital/start node in Stack
        //      add the vertex in DFS,  
        // repeating steps
        //      take out the vertex from stack and start exporing that vertex
        //      add visited vertex in DFS (id DFS does not have this vertex) and stactk, if this vertex has connected vertex
        //

        private graphNode _gnode = new graphNode();
        public void AddChildNode(int val, ref graphNode parent)
        {
            if (parent == null) return;
            if (parent.nodes.Where(n => n.data == val).Any()) return; // same vale node already present

            graphNode temp = new graphNode { data = val, visited = false, nodes = new List<graphNode>() };
            parent.nodes.Add(temp);
        }

        public int SearchDFS(int val, ref graphNode start)
        {
            if (start == null || start.nodes == null || start.nodes.Count < 1) return -1; // not found

            Stack<graphNode> Nodes = new Stack<graphNode>();
            Nodes.Push(start);
            int howfar = 0;
            while (Nodes.Any())
            {
                var popedNode = Nodes.Pop();
                // visit node
                if (popedNode.data == val)
                    return howfar;
                howfar++;

                // explore child nodes
                foreach (var n in popedNode.nodes)
                    Nodes.Push(n);
            }
            return -1; // not found
        }

        public int SearchBFS(int val, ref graphNode start)
        {
            if (start == null || start.nodes == null || start.nodes.Count < 1) return -1; // not found

            Queue<graphNode> Nodes = new Queue<graphNode>();
            Nodes.Enqueue(start);
            int howfar = 0;
            while (Nodes.Any())
            {                
                var popedNode = Nodes.Dequeue();
                // visit node
                if (popedNode.data == val)
                    return howfar;
                howfar++;

                // explore node
                foreach (var n in popedNode.nodes)
                    Nodes.Enqueue(n);
            }
            return -1; // not found
        }
    }

    public class graphNode
    {
        public bool visited;
        public int data;
        public List<graphNode> nodes;
    }
}