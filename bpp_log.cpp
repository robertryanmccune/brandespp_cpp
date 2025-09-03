#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

//vector containing source nodes
vector<int> sources;

// map containing map of non-source nodes to the cluster they belong to
unordered_map<int, int> clusterIds;

// contains an dict-entry for every cluster and node in that cluster
unordered_map<int, unordered_map<int, unordered_map<int, int> > > clusterNodes;

// for every cluster id, contains an adjacency list for nodes within cluster
unordered_map<int, unordered_map<int, vector<int> > > clusterEdges;

// for every cluster id, contains list of frontier nodes in cluster
unordered_map<int, vector<int> > frontierNodes;

int readData( string sourcefile, string clusterfile, string clusterdir) {
	
	/* read sourcefile, tab delimited vert_ids */	
	ifstream inputFile(sourcefile);
	if (!inputFile.is_open()) { cerr << "Error opening sourcefile" <<endl; return 1;}
	string line;
	while( getline(inputFile, line)) {
		istringstream iss(line);
		string field;
		int s;
		while( getline(iss, field, '\t')) {
			s=stoi(field);
			sources.push_back(s);
		}
	}
	inputFile.close();
	
	/* clusters, clusterIds, and clusterNodes */
	set<int> clusters; // contains the ids of every cluster
	int counter=1;
	
	ifstream clusterFile(clusterfile);
	if (!clusterFile.is_open()) { cerr << "Error opening clusterfile" <<endl; return 1;}
	while( getline(clusterFile, line)) {
		int c = stoi(line);
		
		if ( clusterNodes.find(c) == clusterNodes.end() ) {
			clusterNodes[c]=unordered_map<int, unordered_map<int, int> >();
		}
		
		clusters.insert(c);
		
		if ( find(sources.begin(), sources.end(), counter) == sources.end() ) {
			clusterIds[counter] = c;
			clusterNodes[c][counter]=unordered_map<int,int>();
		}
		counter+=1;		
	}
	
	int maxcluster=0;
	set<int>::iterator sitr;
	for( sitr=clusters.begin(); sitr!=clusters.end(); ++sitr) {
		int c = *sitr;
		if (c>maxcluster) maxcluster=c;
		clusterEdges[c]=unordered_map<int, vector<int> >();
		frontierNodes[c]=vector<int>();
	}
	
	
	return 0;
}

void run(string gf, string sf, string cf, string cd) {
	readData(sf, cf, cd);
}

int main(int argc, char* argv[]) {

	if (argc != 5) {
		cout << "usage: ./bpp_log  graph  sources  clusters  clusterdir" << endl;
		return 1;
	}

	string graphfile = argv[1];
	string sourcefile = argv[2];
	string clusterfile = argv[3];
	string clusterdir = argv[4];
	
	run(graphfile, sourcefile, clusterfile, clusterdir);
	
	return 0;  

}