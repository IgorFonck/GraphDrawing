#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/orthogonal/OrthoLayout.h>
#include <ogdf/planarlayout/MixedModelLayout.h>
#include <ogdf/planarity/EmbedderMinDepthMaxFaceLayers.h>
#include <ogdf/planarity/PlanarSubgraphFast.h>
#include <ogdf/planarity/PlanarizationLayout.h>
#include <ogdf/planarity/SubgraphPlanarizer.h>
#include <ogdf/planarity/VariableEmbeddingInserter.h>
#include <ogdf/basic/graph_generators.h>
#include <ogdf/layered/DfsAcyclicSubgraph.h>
#include <ogdf/fileformats/GraphIO.h>
 
using namespace ogdf;
 
int main()
{

    // Grafo comum, sem peso e com lista de adjacência.
    Graph G;
    randomSimpleGraph(G, 20, 40);
 
    DfsAcyclicSubgraph DAS;
    DAS.callAndReverse(G);
 
    // Adiciona atributos ao grafo
    GraphAttributes GA(G,
      GraphAttributes::nodeGraphics | GraphAttributes::nodeType |
      GraphAttributes::edgeGraphics | GraphAttributes::edgeType);
 
    for (node v : G.nodes)
    {
        GA.width(v) /= 2;
        GA.height(v) /= 2;
    }
 
    PlanarizationLayout pl;
 
    // Planariza o grafo para diminuir cruzamentos de arestas
    SubgraphPlanarizer crossMin;
 
    auto* ps = new PlanarSubgraphFast<int>;
    ps->runs(100);
    VariableEmbeddingInserter *ves = new VariableEmbeddingInserter;
    ves->removeReinsert(RemoveReinsertType::All);
 
    crossMin.setSubgraph(ps);
    crossMin.setInserter(ves);
 
    EmbedderMinDepthMaxFaceLayers *emb = new EmbedderMinDepthMaxFaceLayers;
    pl.setEmbedder(emb);
 
    // Layout ortogonal para grafos planares
    OrthoLayout *ol = new OrthoLayout;
    ol->separation(20.0);
    ol->cOverhang(0.4);
    pl.setPlanarLayouter(ol);
 
    pl.call(GA);
 
    //GraphIO::write(GA, "mygraph.gml", GraphIO::writeGML);
    GraphIO::write(GA, "mygraph20.svg", GraphIO::drawSVG);
 
    return 0;
}