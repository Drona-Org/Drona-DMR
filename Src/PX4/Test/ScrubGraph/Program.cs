using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.VisualStudio.GraphModel;

namespace ScrubGraph
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length == 0)
            {
                Console.WriteLine("Usage: ScrubGraph file.dgml");
                Console.WriteLine("This tool removes Category='Active' on Nodes and removes all non-containment links");
                Console.WriteLine("Thereby creating a nice 'template' graph that can be checked in");
                return;
            }

            int removedCategories = 0;
            int removedLinks = 0;
            string fileName = args[0];
            Graph g = Graph.Load(fileName, GraphCommonSchema.Schema, GraphLayoutSchema.Schema);
            using (var scope = new GraphTransactionScope())
            {
                foreach (var node in g.Nodes)
                {
                    foreach (var cat in node.Categories)
                    {
                        if (cat.Id == "Active")
                        {
                            removedCategories++;
                            node.RemoveCategory(cat);
                            break;
                        }
                    }
                }

                foreach (var link in g.Links.ToArray())
                {
                    if (!link.IsContainment)
                    {
                        removedLinks++;
                        g.Links.Remove(link);
                    }
                }
                scope.Complete();
            }
            g.Save(fileName);

            if (removedLinks > 0)
            {
                Console.WriteLine("Removed {0} non containment links", removedLinks);
            }
            if (removedCategories > 0)
            {
                Console.WriteLine("Removed {0} active states", removedCategories);
            }
            if (removedCategories == 0 && removedLinks == 0)
            {
                Console.WriteLine("Graph is clean");
            }
        }

    }

    static class GraphLayoutSchema
    {
        static GraphSchema schema;
        static GraphProperty boundsProperty;
        static GraphProperty labelBoundsProperty;
        static GraphCategory active;

        public static GraphSchema Schema { get { return schema; } }

        static GraphLayoutSchema()
        {
            schema = new GraphSchema("GraphLayoutSchema");
            boundsProperty = schema.Properties.AddNewProperty("Bounds", typeof(System.Windows.Rect));
            labelBoundsProperty = Schema.Properties.AddNewProperty("LabelBounds", typeof(System.Windows.Rect));
            active = Schema.Categories.AddNewCategory("Active");
        }

        public static GraphProperty BoundsProperty {  get { return boundsProperty; } }
        public static GraphProperty LabelBoundsProperty {  get { return labelBoundsProperty; } }
    }
}
