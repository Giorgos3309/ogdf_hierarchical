#include <ogdf/layered/MedianHeuristic.h>
#include <ogdf/layered/OptimalHierarchyLayout.h>
#include <ogdf/layered/OptimalRanking.h>
#include <ogdf/layered/SugiyamaLayout.h>
#include <ogdf/fileformats/GraphIO.h>
#include <vector>
#include <iostream>

 
using namespace ogdf;
 
int main(int argc, char* argv[])
{
    Graph G;
    GraphAttributes GA(G,
      GraphAttributes::nodeGraphics |
      GraphAttributes::edgeGraphics |
      GraphAttributes::nodeLabel |
      GraphAttributes::edgeStyle |
      GraphAttributes::nodeStyle |
      GraphAttributes::nodeTemplate);
    if (!GraphIO::read(GA, G, argv[1]/*"unix-history.gml"*/, GraphIO::readGML)) {
        std::cerr << "Could not load gml file" << std::endl;
        return 1;
    }
 
    SugiyamaLayout SL;
    //SL.setRanking(new OptimalRanking);
    //SL.setCrossMin(new MedianHeuristic);
/* 
    OptimalHierarchyLayout *ohl = new OptimalHierarchyLayout;
    ohl->layerDistance(30.0);
    ohl->nodeDistance(25.0);
    ohl->weightBalancing(0.8);
    SL.setLayout(ohl);
 */
    string outputname = "output";
    outputname += argv[1];
    
    SL.call(GA);
   // GA.boundingBox().width;
    //std::vector<edge> alledges;
    //G.allEdges(alledges);
    //std::cout<<G.numberOfEdges();

    int totaledges = 0;
    for(edge e : G.edges) {
      totaledges+=GA.bends(e).size();
    }
    std::cout<<"number of bends:"<<totaledges<<"\n";
    std::cout<<"number of crossings:"<<SL.numberOfCrossings()<<"\n";
    std::cout<<"number of layers:"<<SL.numberOfLevels()<<"\n";
    std::cout<<"the max number of elements on a layer:"<<SL.maxLevelSize()<<"\n";
    std::cout<<"width:"<<GA.boundingBox().width()<<"\n";
    std::cout<<"height:"<<GA.boundingBox().height()<<"\n";
    GraphIO::write(GA, outputname, GraphIO::writeGML);
    GraphIO::write(GA, outputname+".svg", GraphIO::drawSVG);
 
    return 0;
}
