#include <RelationshipGraph.hpp>
#include <utils.h>
#include <ConnectivityAnalyerAdapter.hpp>

RelationshipGraph::RelationshipGraph() 
{
    adapter = new ConnectivityAnalyerAdapter();
}

RelationshipGraph::~RelationshipGraph() {

}
