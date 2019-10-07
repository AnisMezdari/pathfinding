using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Graph : MonoBehaviour
{
    [SerializeField]
    protected List<Node> list_Node = new List<Node>();
    public List<Node> List_Node { get { return List_Node; } }

    [SerializeField]
    private Node Out;

    [SerializeField]
    private List<Personnage> list_Personnage = new List<Personnage>();

    List<Node> Dijkstrat(Node start,Node end)
    {
        List<Node> path = new List<Node>();

        //If the end is the start
        if(start == end)
        {
            path.Add(start);
            return path;
        }

        //Initialize variable
        List<Node> nodeToVisit = new List<Node>();
        Dictionary<Node, float> distance = new Dictionary<Node, float>();
        Dictionary<Node, Node> preceding = new Dictionary<Node, Node>();

        for(int i=0; i < list_Node.Count; i++)
        {
            nodeToVisit.Add(list_Node[i]);
            distance.Add(list_Node[i], float.MaxValue);
        }
        distance[start] = 0;

        //Algorithm
        while (nodeToVisit.Count != 0)
        {
           //find the smallest distance
           float distmin = float.MaxValue;
           Node currentNode = null;

            for(int i=0;i<nodeToVisit.Count;i++)
            {
                if (distance[nodeToVisit[i]] <= distmin)
                {
                    currentNode = nodeToVisit[i];
                    distmin = distance[nodeToVisit[i]];
                }
            }

            //Remove the node from the list
            nodeToVisit.Remove(currentNode);

            //if we find the end node
            if( currentNode == end)
            {
                //insert into path the node of the path
                while(preceding.ContainsKey(currentNode))
                {
                    path.Add(currentNode);
                    currentNode = preceding[currentNode];
                }

                //insert the start node in the path
                path.Add(currentNode);
               
                break;
            }
            

            for(int i=0; i < currentNode.Neighbour.Count;i++)
            {
                Node currentNeighbour = currentNode.Neighbour[i];

                //get the distance
                float dist = Vector3.Distance(currentNode.transform.position, currentNeighbour.transform.position);

                float newDist = distance[currentNode] + dist;

                //test to know if this new distance is lower
                if(newDist < distance[currentNeighbour])
                {
                    distance[currentNeighbour] = newDist;
                    preceding[currentNeighbour] = currentNode;
                }
            }

        }
        return path;
         
    }

    List<Node> Astar(Node Start, Node End)
    {
        List<Node> closedList = new List<Node>();
        List<Node> openList = new List<Node>();
        Dictionary<Node, Node> preceding = new Dictionary<Node, Node>();
        Dictionary<Node, float> nodeCost = new Dictionary<Node, float>();

        List<Node> path = new List<Node>();

        openList.Add(Start);

        for(int i =0; i < list_Node.Count; i++) 
            nodeCost.Add(list_Node[i], float.MaxValue);

        while(openList.Count != 0)
        {
            //Find the node with the smallest cost
            float min = nodeCost[openList[0]];
            int index = 0;

            for (int i = 1; i < openList.Count; i++)
                if (min < nodeCost[openList[i]])
                {
                    min = nodeCost[openList[i]];
                    index = i;
                }

            Node currentNode = openList[index];
            openList.Remove(currentNode);

            //If the node is the end
            if(currentNode == End)
            {
                while (preceding.ContainsKey(currentNode))
                {
                    path.Add(currentNode);
                    currentNode = preceding[currentNode];
                }

                //insert the start node in the path
                path.Add(currentNode);

                return path;
            }
            else
            {
                foreach(Node currentNeighbour in currentNode.Neighbour)
                {
                    if (closedList.Contains(currentNeighbour))
                        continue;
                    else
                    {
                        float predictDist = Vector3.Distance(currentNeighbour.transform.position, End.transform.position);

                        if( (predictDist + currentNeighbour.Cost) < nodeCost[currentNeighbour])
                        {
                            nodeCost[currentNeighbour] = (predictDist + currentNeighbour.Cost);
                            openList.Add(currentNeighbour);
                            preceding[currentNeighbour] = currentNode;
                        }
                    }
                }
                closedList.Add(currentNode);
            }
                
        }

        return path;
    }

    // Start is called before the first frame update
    void Start()
    {
    
    }

    void ChangeColor(List<Node> listNode, Color c)
    {
        foreach (Node n in listNode)
            n.ChangeColor(c);
    }
    // Update is called once per frame
    void Update()
    {
        Personnage Hero = new Personnage();
        Hero = list_Personnage[0];
        Personnage Monster = new Personnage();
        Monster = list_Personnage[1];

        if(Hero.Position == Out)
        {
            Application.LoadLevel("WinScene");
        }

        if (Hero.Position == Monster.Position)
        {
            Application.LoadLevel("LooseScene");
        }

        if (Input.GetKeyUp("up"))
        {
            foreach(Node neighbour in Hero.Position.Neighbour)
            {
                if(neighbour.transform.position.y > Hero.Position.transform.position.y)
                {
                    Hero.Position = neighbour;
                    Monster.Position = Dijkstrat(Hero.Position, Monster.Position)[1];
                    break;
                }
            }
           
        }
        if (Input.GetKeyUp("down"))
        {
            foreach (Node neighbour in Hero.Position.Neighbour)
            {
                if (neighbour.transform.position.y < Hero.Position.transform.position.y)
                {
                    Hero.Position = neighbour;
                    Monster.Position = Dijkstrat(Hero.Position, Monster.Position)[1];
                    break;
                }
            }
           
        }
        if (Input.GetKeyUp("left"))
        {
            foreach (Node neighbour in Hero.Position.Neighbour)
            {
                if (neighbour.transform.position.x < Hero.Position.transform.position.x)
                {
                    Hero.Position = neighbour;
                    Monster.Position = Dijkstrat(Hero.Position, Monster.Position)[1];
                    break;
                }
            }
        }
        if (Input.GetKeyUp("right"))
        {
            foreach (Node neighbour in Hero.Position.Neighbour)
            {
                if (neighbour.transform.position.x > Hero.Position.transform.position.x)
                {
                    Hero.Position = neighbour;
                    Monster.Position = Dijkstrat(Hero.Position, Monster.Position)[1];
                    break;
                }
            }
        }

        foreach (Node n in list_Node)
        {
            if (Astar(n, list_Personnage[0].Position).Count > 3)
            {
                n.ChangeColor(Color.black);
            }
            else
            {
                n.ChangeColor(n.ColorNode);
            }
        }
       
        ChangeColor(Dijkstrat(Hero.Position, Monster.Position), Color.red);

        foreach (Personnage p in list_Personnage)
        {
            p.Position.ChangeColor(p.Color);
        }

        Out.ChangeColor(Color.green);
    }
}
